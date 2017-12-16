#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "ComponentCanvas.h"
#include "ComponentCanvasRenderer.h"
#include "ComponentRectTransform.h"
#include "ComponentInteractive.h"
#include "ComponentInputText.h"
#include "ComponentImage.h"
#include "ResourceTexture.h"
#include "EventSystem.h"
#include "ModuleInput.h"
#include "SDL/include\SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#define INDICES_NUM 4
#define DEFAULT_PIVOT 0.5f
ComponentCanvas::ComponentCanvas(GameObject* my_go): Component(my_go)
{
	component_name = "Canvas";
	type = CANVAS;
	EventChar event_str;
	UUID = App->GenerateRandom();
	event_str.Create("AddStr", this, &ComponentCanvas::EventString, UUID);
	EventS->AddEvent(event_str);
}


ComponentCanvas::~ComponentCanvas()
{
}

void ComponentCanvas::OnPlay()
{
	on_ejecution = true;
}

void ComponentCanvas::Update(float dt)
{
	App->renderer3D->AddCanvasToRender(this);
	my_go->GetRectTransform()->SetWidth(canvas_data.size.x);
	my_go->GetRectTransform()->SetHeight(canvas_data.size.y);
	my_go->GetRectTransform()->SetBlock(true);
	UpdateInteractiveMap();
	UpdateInteractive();
	UpdateFocus();
	DebugDraw();

}

void ComponentCanvas::OnStop()
{
	on_ejecution = false;
}

void ComponentCanvas::Render()
{
	//if (on_ejecution)
		SetUpRender();
	std::list<ComponentCanvasRenderer*>::iterator it = canvas_render.begin();
	for (; it != canvas_render.end(); it++)
	{
		glPushMatrix();
		glMultMatrixf((float*)&(*it)->my_go->GetTransposedMatrix());

		if (!(*it)->ProcessComponent())
		{
			glPopMatrix();
			continue;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		if ((*it)->GetImageID() != -1)
		{
			glBindTexture(GL_TEXTURE_2D, (*it)->GetImageID());
			//	glColor4f(image->GetImage()->GetRGBA().x, image->GetImage()->GetRGBA().y, image->GetImage()->GetRGBA().z, image->GetImage()->GetRGBA().w);
		}

		glBindBuffer(GL_ARRAY_BUFFER, (*it)->GetVBO());
		glVertexPointer(3, GL_FLOAT, sizeof(CanvasVertex), NULL);
		//glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
		glTexCoordPointer(2, GL_FLOAT, sizeof(CanvasVertex), (void*)offsetof(CanvasVertex, tex_coords));
		glBindBuffer(GL_ARRAY_BUFFER, 0);



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->GetEBO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
	canvas_render.clear();
	//if (on_ejecution)
		ResetRender();
	/*
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_CLAMP);
	*/
	
}

void ComponentCanvas::CleanUp()
{
	EventS->EraseEventChar("AddStr", UUID);
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
	glOrtho(0.0f, canvas_data.size.x, canvas_data.size.y, 0.0f, -1.0f, +1.0f);

	//gluOrtho2D(-100, 100, -100, 100);
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
	this->canvas_render.push_back(canvas_render);
	//canvas_render->SetUpCanvas();
	
}

void ComponentCanvas::UpdateInteractive()
{
	std::multimap<float, ComponentInteractive*>::reverse_iterator map_iterator;
	bool is_on_hover = false;
	for (map_iterator = interactive_z_map.rbegin();map_iterator != interactive_z_map.rend(); ++map_iterator)
	{
		int x;
		int y;

		ComponentRectTransform* transform = map_iterator->second->transform;
		
		int mouse_x = App->input->GetMouseX() * transform->GetPivot().x;
		int mouse_y = App->input->GetMouseY() * transform->GetPivot().y;
		
		x = transform->GetGlobalMatrix().TranslatePart().x;
		y = transform->GetGlobalMatrix().TranslatePart().y;
	    
		x -= transform->GetWidth() * transform->GetPivot().x;
		y -= transform->GetHeight() * transform->GetPivot().y;

		if (mouse_x >= x  && mouse_x <= x + transform->GetWidth() &&
			mouse_y >= y  && mouse_y <= y + transform->GetHeight())
		{
			if(is_on_hover == false)
			{
				current_focus = map_iterator->second;

				is_on_hover = true;
				
				current_focus->has_focus = true;

				if (map_iterator->second->states == IDLE)
				{
					map_iterator->second->OnHover();

				}

				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
				{
					map_iterator->second->OnClick();
				}
				else if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_IDLE && map_iterator->second->states == DOWN)
				{
					map_iterator->second->OnHover();
				}
			}
			else if(map_iterator->second->states == HOVER || map_iterator->second->states == DOWN)
			{
				map_iterator->second->OnIdle();
			}
				
		}
		else if(map_iterator->second->states == HOVER || map_iterator->second->states == DOWN)
		{
			map_iterator->second->OnIdle();
		}
	}
}

void ComponentCanvas::UpdateDrag()
{
	ComponentRectTransform* transform = current_focus->transform;

	if (current_focus->is_dragable == true)
	{
		
		int delta_x = App->input->GetMouseXMotion() * transform->GetPivot().x;
		int delta_y = App->input->GetMouseYMotion() * transform->GetPivot().y;

		if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			transform->position.x += delta_x;
			transform->position.y += delta_y;
		}
	 }
}

void ComponentCanvas::EventString(const char * str)
{
	if (current_focus != nullptr)
	{
		if (current_focus->type == CANVAS_INPUT_TEXT)
		{
			((ComponentInputText*)current_focus)->AddText(str);
			((ComponentInputText*)current_focus)->CallUpdate();

		}
	}
}


void ComponentCanvas::UpdateFocus()
{
	bool is_on_hover = false;
	std::multimap<float, ComponentInteractive*>::iterator map_iterator;

	if (current_focus != nullptr)
	{
		if (current_focus->type == CANVAS_INPUT_TEXT)
		{
			UpdateInput();
		}
		else if(current_focus->type == CANVAS_IMDRAG)
		{
			UpdateDrag();
		}
		if (current_focus->has_focus == true)
		{
			if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
			{
				for (map_iterator = interactive_x_map.begin(); map_iterator != interactive_x_map.end(); ++map_iterator)
				{
					if (current_focus == map_iterator->second)
					{
						current_focus->has_focus = false;
						++map_iterator;
						if (map_iterator == interactive_x_map.end())
						{
							map_iterator = interactive_x_map.begin();
						}
						current_focus = map_iterator->second;
						current_focus->has_focus = true;
						return;
					}

				}
			}
			else if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
			{
				current_focus->OnClick();
			}
		}	
	}
	else
	{
		if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		{
			if (!interactive_x_map.empty())
			{
				current_focus = interactive_x_map.begin()->second;
				current_focus->has_focus = true;
			}
		}
	}
}



void ComponentCanvas::UpdateInput()
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		((ComponentInputText*)current_focus)->MoveLeft();
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		((ComponentInputText*)current_focus)->MoveRight();
	}
	else if (App->input->GetKey(SDL_SCANCODE_END) == KEY_DOWN)
	{
		((ComponentInputText*)current_focus)->MoveToEnd();
	}
	else if (App->input->GetKey(SDL_SCANCODE_HOME) == KEY_DOWN)
	{
		((ComponentInputText*)current_focus)->MoveToStart();
	}
	else if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
	{
	
		if (((ComponentInputText*)current_focus)->EraseText(((ComponentInputText*)current_focus)->GetCurrentPos()-1))
		{
		}
		((ComponentInputText*)current_focus)->CallUpdate();

	}
	else if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
	{
		((ComponentInputText*)current_focus)->EraseText(((ComponentInputText*)current_focus)->GetCurrentPos());
		((ComponentInputText*)current_focus)->CallUpdate();

	}
}



void ComponentCanvas::UpdateInteractiveMap()
{
	interactive_z_map.clear();
	interactive_x_map.clear();

	for (int i = 0; i < interactive_array.size(); i++)
	{
		interactive_z_map.insert(std::pair<float, ComponentInteractive*>(interactive_array[i]->transform->GetDepth(), interactive_array[i]));
		interactive_x_map.insert(std::pair<float, ComponentInteractive*>(interactive_array[i]->transform->position.x, interactive_array[i]));
	}
}

CanvasBuffer::CanvasBuffer()
{
}



void ComponentCanvas::DebugDraw()
{
	glBegin(GL_LINES);
	glLineWidth(1.0f);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(my_go->GetRectTransform()->GetSouthWest().x, my_go->GetRectTransform()->GetSouthWest().y, my_go->GetRectTransform()->GetSouthWest().z);
	glVertex3f(my_go->GetRectTransform()->GetNorthWest().x, my_go->GetRectTransform()->GetNorthWest().y, my_go->GetRectTransform()->GetNorthWest().z);
	
	glVertex3f(my_go->GetRectTransform()->GetNorthWest().x, my_go->GetRectTransform()->GetNorthWest().y, my_go->GetRectTransform()->GetNorthWest().z);
	glVertex3f(my_go->GetRectTransform()->GetNorthEeast().x, my_go->GetRectTransform()->GetNorthEeast().y, my_go->GetRectTransform()->GetNorthEeast().z);

	glVertex3f(my_go->GetRectTransform()->GetNorthEeast().x, my_go->GetRectTransform()->GetNorthEeast().y,my_go->GetRectTransform()->GetNorthEeast().z);
	glVertex3f(my_go->GetRectTransform()->GetSouthEast().x, my_go->GetRectTransform()->GetSouthEast().y, my_go->GetRectTransform()->GetSouthEast().z);

	glVertex3f(my_go->GetRectTransform()->GetSouthEast().x, my_go->GetRectTransform()->GetSouthEast().y, my_go->GetRectTransform()->GetSouthEast().z);
	glVertex3f(my_go->GetRectTransform()->GetSouthWest().x, my_go->GetRectTransform()->GetSouthWest().y, my_go->GetRectTransform()->GetSouthWest().z);

	glEnd();
}
