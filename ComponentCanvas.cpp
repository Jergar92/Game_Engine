#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ComponentCanvas.h"
#include "ComponentCanvasRenderer.h"
#include "ComponentImage.h"
#include "ResourceTexture.h"
#include "SDL/include\SDL.h"

#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#define INDICES_NUM 4
ComponentCanvas::ComponentCanvas(GameObject* my_go): Component(my_go)
{
	component_name = "Canvas";
	type = CANVAS;


}


ComponentCanvas::~ComponentCanvas()
{
}

void ComponentCanvas::Update(float dt)
{
	App->renderer3D->AddCanvasToRender(this);

}

void ComponentCanvas::Render()
{
	SetUpRender();
	SetUpCanvas();

	std::map<uint, CanvasBuffer*>::const_iterator it = canvas_buffer.begin();
	for (; it != canvas_buffer.end(); it++)
	{
		if (!it->second->indices.empty() && !it->second->vertices.empty())
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			if (it->second->texture_id != -1)
			{
				glBindTexture(GL_TEXTURE_2D, it->second->texture_id);
			//	glColor4f(image->GetImage()->GetRGBA().x, image->GetImage()->GetRGBA().y, image->GetImage()->GetRGBA().z, image->GetImage()->GetRGBA().w);
			}
			glBindBuffer(GL_ARRAY_BUFFER, it->second->VBO);
			glVertexPointer(3, GL_FLOAT, sizeof(CanvasVertex), NULL);
			//glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
			glTexCoordPointer(2, GL_FLOAT, sizeof(CanvasVertex), (void*)offsetof(CanvasVertex, tex_coords));
			glBindBuffer(GL_ARRAY_BUFFER, 0);



			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, it->second->EBO);
			glDrawElements(GL_TRIANGLES, it->second->indices.size(), GL_UNSIGNED_INT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, 0);
			it->second->vertices.clear();
			it->second->indices.clear();
		}
	}
	ResetRender();
	/*
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_CLAMP);
	*/
	
}

void ComponentCanvas::SetUpCanvasSize(SDL_Window *window)
{
	int w, h;
	int display_w, display_h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_GL_GetDrawableSize(window, &display_w, &display_h);
	canvas_data.size = float2((float)w, (float)h);
	canvas_data.draw_size = float2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);
}

void ComponentCanvas::SetUpCanvas()
{

	std::map<uint, CanvasBuffer*>::const_iterator it = canvas_buffer.begin();
	for (; it != canvas_buffer.end(); it++)
	{
		if (!it->second->indices.empty() && !it->second->vertices.empty())
		{
			glBindBuffer(GL_ARRAY_BUFFER, it->second->VBO);
			glBufferData(GL_ARRAY_BUFFER, it->second->vertices.size() * sizeof(CanvasVertex), &it->second->vertices[0], GL_STATIC_DRAW);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, it->second->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, it->second->indices.size() * sizeof(uint), &it->second->indices[0], GL_STATIC_DRAW);
			//set bind buffer glBindBuffer to 0
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


			//set bind buffer glBindBuffer to 0
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	
}

void ComponentCanvas::SetUpRender()
{

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
	glGetIntegerv(GL_VIEWPORT, last_viewport);
	glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);

	int fb_width = (int)(canvas_data.size.x * canvas_data.draw_size.x);
	int fb_height = (int)(canvas_data.size.y * canvas_data.draw_size.y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//GLORTHO??
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ComponentCanvas::ResetRender()
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();

	glPolygonMode(GL_FRONT, last_polygon_mode[0]);
	glPolygonMode(GL_BACK, last_polygon_mode[1]);

	glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
	glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}

void ComponentCanvas::AddCanvasRender(ComponentCanvasRenderer * canvas_render)
{
	uint texture_id = (canvas_render->image->GetImage()!=nullptr)? canvas_render->image->GetImage()->GetID():0;
	std::map<uint, CanvasBuffer*>::iterator it = canvas_buffer.find(texture_id);
	CanvasBuffer* buffer=nullptr;

	if (it != canvas_buffer.end())
	{
		buffer = it->second;
	}
	else
	{
		buffer = new CanvasBuffer();
		canvas_buffer[texture_id] = buffer;
		buffer->texture_id = texture_id;
		glGenBuffers(1, &buffer->VBO);
		glGenBuffers(1, &buffer->EBO);
	}
		CanvasVertex ver1;
		ImageRect tmp_rect = canvas_render->image->GetImageRect();
		int count = buffer->vertices.size()/4;

		for (int i = 0; i < 4; i++)
		{
			ver1.position = float3(tmp_rect.vertices[i*3+0], tmp_rect.vertices[i*3+1], 0);

			if(i==0)
			ver1.tex_coords = canvas_render->image->GetUV0();
			else if (i == 1)
				ver1.tex_coords = float2(canvas_render->image->GetUV0().x, canvas_render->image->GetUV1().y);
			else if (i == 2)
				ver1.tex_coords = canvas_render->image->GetUV1();
			else if (i == 3)
				ver1.tex_coords = float2(canvas_render->image->GetUV1().x, canvas_render->image->GetUV0().y);
			buffer->vertices.push_back(ver1);
		}
		
		int value = INDICES_NUM*count;
	
		buffer->indices.push_back(value+0);
		buffer->indices.push_back(value+1);
		buffer->indices.push_back(value+2);
		buffer->indices.push_back(value+2);
		buffer->indices.push_back(value+3);
		buffer->indices.push_back(value+0);
}

CanvasBuffer::CanvasBuffer()
{
}
