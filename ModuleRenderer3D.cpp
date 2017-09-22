#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) 
{
	name = "Render";

}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Awake(const JSON_Object* data)
{
	LOG("Creating 3D Renderer context");

	bool ret = true;

	JSON_Object * render_data = json_object_dotget_object(data, name.c_str());
	vsync = json_object_dotget_number(render_data, "vsync");
	background_color.x =json_object_dotget_number(render_data, "background_r");
	background_color.y = json_object_dotget_number(render_data, "background_g");
	background_color.z = json_object_dotget_number(render_data, "background_b");

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
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
		GLenum error = glGetError();
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
		lights[0].ambient.Set(1.0f, 1.0f, 1.0f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(App->window->GetWidth(), App->window->GetHeight());

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	ImGui_ImplSdlGL2_NewFrame(App->window->window);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());
	
	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();
		
	return UPDATE_CONTINUE;
}

// Gui Update present buffer to screen
void ModuleRenderer3D::GuiUpdate()
{

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		static bool vsync_check = vsync != 0;
		if(ImGui::Checkbox("Vsync", &vsync_check))
		{
			vsync = 1 - vsync;
		}
		ImGui::PushItemWidth(150);

		ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha;
		flags |= ImGuiColorEditFlags_NoSidePreview;
		flags |= ImGuiColorEditFlags_PickerHueBar;
		flags |= ImGuiColorEditFlags_RGB;

		if(ImGui::ColorPicker4("Background Color##4", (float*)&background_color, flags, NULL))
		{
			glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
		}
		ImGui::PopItemWidth();

	}
}
// Update present buffer to screen
update_status ModuleRenderer3D::Update(float dt)
{
	return UPDATE_CONTINUE;
}
// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	ImGui::Render();

		SDL_GL_SwapWindow(App->window->window);	
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
bool ModuleRenderer3D::SaveConfig(const JSON_Object* data)
{
	bool ret = true;
	JSON_Object* render_data = json_object_dotget_object(data, name.c_str());

	json_object_dotset_number(render_data, "vsync", vsync);
	json_object_dotset_number(render_data, "background_r", background_color.x);
	json_object_dotset_number(render_data, "background_g", background_color.y);
	json_object_dotset_number(render_data, "background_b", background_color.z);

	return ret;
}

bool ModuleRenderer3D::LoadConfig(const JSON_Object* data)
{
	bool ret = true;
	JSON_Object * render_data = json_object_dotget_object(data, name.c_str());
	int vsync = json_object_dotget_number(render_data, "vsync");
	background_color.x = json_object_dotget_number(render_data, "background_r");
	background_color.y = json_object_dotget_number(render_data, "background_g");
	background_color.z = json_object_dotget_number(render_data, "background_b");
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

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
