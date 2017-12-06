#include "UI.h"
#include "ComponentCanvasRenderer.h"
#include "ComponentImage.h"
#include "ResourceTexture.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#define INDICES_NUM 4
UI::UI()
{
}


UI::~UI()
{
}

void UI::Render()
{
	SetUpCanvas();
	/*
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_CLAMP);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	*/
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

	/*
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_CLAMP);
	*/
	
}

void UI::SetUpCanvas()
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

void UI::AddCanvasRender(ComponentCanvasRenderer * canvas_render)
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
