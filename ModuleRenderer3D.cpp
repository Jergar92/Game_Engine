#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ComponentCamera.h"
#include "ComponentMeshRenderer.h"
#include "UI.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui/imgui_impl_sdl.h"



#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "Glew/lib/Release/Win32/glew32.lib") /* link glew32 lib   */

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) 
{
	name = "Render";

}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Awake(const JSONConfig& data)
{
	camera = App->camera->GetCamera();
	//BROFILER_CATEGORY("Module Render Awake", Profiler::Color::AliceBlue);

	LOG("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	gl_context = SDL_GL_CreateContext(App->window->window);
	if (gl_context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (ret == true)
	{

		//Use Vsync
		if (SDL_GL_SetSwapInterval(vsync) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		
		//Check for error
		GLenum error = glewInit();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing glew! %s\n", glewGetString(error));
			ret = false;
		}
		

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glClearDepth(1.0f);
		//Initialize clear color
		glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.5f, 0.5f, 0.5f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		lights[0].Active(true);

		RenderOptions();
	}
	LoadConfig(data);
	// Projection matrix for
	OnResize(App->window->GetWidth(), App->window->GetHeight());

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//BROFILER_CATEGORY("Module Render PreUpdate", Profiler::Color::AliceBlue);
	
	ImGui_ImplSdlGL2_NewFrame(App->window->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (camera->matrix_update == true)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((GLfloat*)camera->GetProjectionMatrix());
		camera->matrix_update = false;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera->GetViewMatrix());
	
	

	// light 0 on cam pos
	//lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();
		
	return UPDATE_CONTINUE;
}

// Gui Update present buffer to screen
void ModuleRenderer3D::GuiConfigUpdate()
{
	if (ImGui::CollapsingHeader(name.c_str()))
	{
		static bool vsync_check = vsync != 0;
		if (ImGui::Checkbox("Vsync", &vsync_check))
		{
			vsync = 1 - vsync;
		}
		ImGui::PushItemWidth(150);

		ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
		flags |= ImGuiColorEditFlags_NoSidePreview;
		flags |= ImGuiColorEditFlags_PickerHueBar;
		flags |= ImGuiColorEditFlags_RGB;

		if (ImGui::ColorPicker4("Background Color##4", (float*)&background_color, flags, NULL))
		{
			glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
		}

		if (ImGui::Checkbox("Depth test##depth", &depth_test))
			(depth_test) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
		//Culling Option
		if (ImGui::Checkbox("Cull face##cull_face", &cull_face))
			(cull_face) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
		if (cull_face)
		{
			if (ImGui::RadioButton("Front facing culling##gl_ccw", &front_face, 1))
				glFrontFace(GL_CCW);
			ImGui::SameLine();
			if (ImGui::RadioButton("Back facing culling##gl_cw", &front_face, 0))
				glFrontFace(GL_CW);
		}
		//------------------------------------
		//Light Option
		if (ImGui::Checkbox("Lighting##lighting", &lighting))
			(lighting) ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
		if (lighting)
		{
			ImGui::SliderFloat4("Ambient light", light_ambient, 0.0f, 1.0f, "%0.1f");
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
		}
		//Color Option
		if (ImGui::Checkbox("Color material##color_material", &color_material))
			(color_material) ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);
		if (color_material)
		{
			ImGui::SliderFloat4("Ambient color", color_ambient, 0.0f, 1.0f, "%0.1f");
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_ambient);

			ImGui::SliderFloat4("Diffuse color", color_diffuse, 0.0f, 1.0f, "%0.1f");
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_diffuse);

		}
		//-------------------------------------
		if (ImGui::Checkbox("Texture 2D##texture_2d", &texture_2d))
			(texture_2d) ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);


		//FOG
		if (ImGui::Checkbox("FOG##fog", &fog))
			(fog) ? glEnable(GL_FOG) : glDisable(GL_FOG);
		if (fog)
		{

			if (ImGui::SliderFloat("FOG Density", &fog_density, 0.0f, 1.0f, "%0.3f"))
			{
				GLfloat GL_fog_density = fog_density;
				glFogfv(GL_FOG_DENSITY, &GL_fog_density);
			}
			if (ImGui::SliderFloat4("FOG_color", fog_color, 0.0f, 1.0f, "%0.1"))
			{
				GLfloat GL_fog_color[4] = { fog_color[0],fog_color[1], fog_color[2], fog_color[3] };
				glFogfv(GL_FOG_COLOR, GL_fog_color);
			}
		}
		//--------------------------------------------------------------
		if (ImGui::Checkbox("Wireframe##wireframe", &wireframe))
			(wireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		ImGui::PopItemWidth();


	}
}
update_status ModuleRenderer3D::GuiUpdate()
{

	return UPDATE_CONTINUE;
}
// Update present buffer to screen
update_status ModuleRenderer3D::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	//App->scene->GetScene()->Draw();
	DrawGameObject();
	/*
	void ImGui_ImplSdl_RenderDrawLists(ImDrawData* draw_data)
	{
	// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
	ImGuiIO& io = ImGui::GetIO();
	int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0)
	return;
	draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	// We are using the OpenGL fixed pipeline to make the example code simpler to read!
	// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers, polygon fill.
	GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
	GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
	GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound

	// Setup viewport, orthographic projection matrix
	glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Render command lists
	#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
	const ImDrawList* cmd_list = draw_data->CmdLists[n];
	const ImDrawVert* vtx_buffer = cmd_list->VtxBuffer.Data;
	const ImDrawIdx* idx_buffer = cmd_list->IdxBuffer.Data;
	glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (const GLvoid*)((const char*)vtx_buffer + OFFSETOF(ImDrawVert, pos)));
	glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (const GLvoid*)((const char*)vtx_buffer + OFFSETOF(ImDrawVert, uv)));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (const GLvoid*)((const char*)vtx_buffer + OFFSETOF(ImDrawVert, col)));

	for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
	{
	const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
	if (pcmd->UserCallback)
	{
	pcmd->UserCallback(cmd_list, pcmd);
	}
	else
	{
	glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
	glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
	glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);
	}
	idx_buffer += pcmd->ElemCount;
	}
	}
	#undef OFFSETOF

	// Restore modified state
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glPolygonMode(GL_FRONT, last_polygon_mode[0]); glPolygonMode(GL_BACK, last_polygon_mode[1]);
	glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
	glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
	}

	*/
	if (lighting)glDisable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_CLAMP);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	Canvas->Render();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_CLAMP);
	ImGui::Render();

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat*)camera->GetProjectionMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera->GetViewMatrix());

	if (lighting)glEnable(GL_LIGHTING);

	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
bool ModuleRenderer3D::SaveConfig(JSONConfig& data)const
{
	bool ret = true;

	data.SetInt(vsync,"vsync");


	data.SetFloat(background_color.x, "background_r");
	data.SetFloat(background_color.y, "background_g");
	data.SetFloat(background_color.z, "background_b");
	//OpenGL Enable/Disable

	data.SetBool(depth_test, "depth_test");
	data.SetFloat(depth, "depth");

	data.SetBool(cull_face, "cull_face");
	data.SetInt(front_face, "front_face");

	data.SetBool(lighting, "lighting");
	data.SetFloat(light_ambient[0], "light_ambient_r");
	data.SetFloat(light_ambient[1], "light_ambient_g");
	data.SetFloat(light_ambient[2], "light_ambient_b");
	data.SetFloat(light_ambient[3], "light_ambient_a");

	data.SetBool(color_material, "color_material");
	data.SetFloat(color_ambient[0], "color_ambient_r");
	data.SetFloat(color_ambient[1], "color_ambient_g");
	data.SetFloat(color_ambient[2], "color_ambient_b");
	data.SetFloat(color_ambient[3], "color_ambient_a");
	data.SetFloat(color_diffuse[0], "color_diffuse_r");
	data.SetFloat(color_diffuse[1], "color_diffuse_g");
	data.SetFloat(color_diffuse[2], "color_diffuse_b");
	data.SetFloat(color_diffuse[3], "color_diffuse_a");

	data.SetBool(texture_2d, "texture_2d");

	data.SetBool(fog,"fog");
	data.SetFloat(fog_density,"fog_density");
	data.SetFloat(fog_color[0], "fog_color_r");
	data.SetFloat(fog_color[1], "fog_color_g");
	data.SetFloat(fog_color[2], "fog_color_b");
	data.SetFloat(fog_color[3], "fog_color_a");


	return ret;
}

bool ModuleRenderer3D::LoadConfig(const JSONConfig& data)
{
	bool ret = true;
	vsync = data.GetInt("vsync");

	background_color.x = data.GetFloat("background_r");
	background_color.y = data.GetFloat("background_g");
	background_color.z = data.GetFloat("background_b");


	//OpenGL Enable/Disable
	depth_test = data.GetBool("depth_test");
	depth = data.GetFloat("depth");

	cull_face = data.GetBool("cull_face");
	front_face = data.GetInt("front_face");

	lighting = data.GetBool("lighting");
	light_ambient[0] = data.GetFloat("light_ambient_r");
	light_ambient[1] = data.GetFloat("light_ambient_g");
	light_ambient[2] = data.GetFloat("light_ambient_b");
	light_ambient[3] = data.GetFloat("light_ambient_a");

	color_material = data.GetBool("color_material");
	color_ambient[0] = data.GetFloat("color_ambient_r");
	color_ambient[1] = data.GetFloat("color_ambient_g");
	color_ambient[2] = data.GetFloat("color_ambient_b");
	color_ambient[3] = data.GetFloat("color_ambient_a");

	color_diffuse[0] = data.GetFloat("color_diffuse_r");
	color_diffuse[1] = data.GetFloat("color_diffuse_g");
	color_diffuse[2] = data.GetFloat("color_diffuse_b");
	color_diffuse[3] = data.GetFloat("color_diffuse_a");

	texture_2d = data.GetBool("texture_2d");

	fog = data.GetBool("fog");
	fog_density = data.GetFloat("fog_density");
	fog_color[0] = data.GetFloat("fog_color_r");
	fog_color[1] = data.GetFloat("fog_color_g");
	fog_color[2] = data.GetFloat("fog_color_b");
	fog_color[3] = data.GetFloat("fog_color_a");

	RenderOptions();
	//Initialize clear color
	glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
	//Use Vsync
	if (SDL_GL_SetSwapInterval(vsync) < 0)
		LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		
	return ret;
}
// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");
	ImGui_ImplSdlGL2_Shutdown();
	SDL_GL_DeleteContext(gl_context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);

//	ProjectionMatrix = float4x4::D3DPerspProjLH(0.125f, 512.0f, width, height);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::AddMeshToRender(ComponentMeshRenderer * add)
{
	go_mesh.push_back(add);

}


ComponentCamera * ModuleRenderer3D::GetCamera() const
{
	return camera;
}

void ModuleRenderer3D::SetCamera(ComponentCamera * cam)
{
	if (cam == nullptr)
	{
		camera = App->camera->GetCamera();
	}
	else
	{
		camera = cam;
	}	
}

void ModuleRenderer3D::RenderOptions()
{
	(depth_test) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

	(cull_face) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

	if (cull_face)
	{
		(front_face) ? glFrontFace(GL_CCW) : glFrontFace(GL_CW);

	}
	(lighting) ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);

	(color_material) ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);
	if (color_material)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_diffuse);

	}
	(texture_2d) ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);

	(fog) ? glEnable(GL_FOG) : glDisable(GL_FOG);



	if (fog)
	{
		GLfloat GL_fog_density = fog_density;
		glFogfv(GL_FOG_DENSITY, &GL_fog_density);
		GLfloat GL_fog_color[4] = { fog_color[0],fog_color[1], fog_color[2], fog_color[3] };
		glFogfv(GL_FOG_COLOR, GL_fog_color);
	}
	(wireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void ModuleRenderer3D::DrawGameObject()
{
	if (go_mesh.empty())
		return;
	for (std::vector<ComponentMeshRenderer*>::iterator it = go_mesh.begin(); it < go_mesh.end(); it++)
	{
		(*it)->Draw();
	}
	go_mesh.clear();
}


