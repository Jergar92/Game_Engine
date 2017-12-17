#include "ComponentText.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "ResourceFont.h"
#include "GameObject.h"

#include "imgui/imgui.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SDL\include\SDL.h"
#include "SDL_ttf\include\SDL_ttf.h"
#define MIN_SIZE 6 
#define MAX_SIZE 50
ComponentText::ComponentText(GameObject* my_go):Component(my_go)
{
	component_name = "text";
	type = CANVAS_TEXT;

}


ComponentText::~ComponentText()
{
}

void ComponentText::InspectorUpdate()
{
	//TODO BUTTON
	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);

	if (ImGui::BeginPopupContextItem("go_options"))
	{
		//Scene GO protection
		if (ImGui::Button("Delete Component"))
		{
			DeleteComponent();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	if (node_open)
	{
		if (text != nullptr)
		{
			ImGui::Text("Texture Path:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", text->GetOrignalName().c_str());		
			if (ImGui::InputText("Text##text_input", (char*)input_text.c_str(), max_input, ImGuiInputTextFlags_EnterReturnsTrue))
				SetString(input_text.c_str());
			if (ImGui::ColorEdit4("##image_rgba", color.ptr()))
			{
				UpdateText();
			}

			if (ImGui::DragInt("Font Size##font_size", &text->size, 1, MIN_SIZE, MAX_SIZE))
			{
				if (text->size < MIN_SIZE)
					text->size = MIN_SIZE;
				if (text->size> MAX_SIZE)
					text->size = MAX_SIZE;
				text->UnLoadInMemory();
				text->LoadInMemory();
				UpdateText();
			}
			ImGui::DragInt("Max leght ##max_lenght", &max_input, 1, 0, 20);
		
		}

		if (ImGui::Button("Select Font"))
		{
			show_resource_font_windows = true;
		}
		ImGui::TreePop();
	}
	if (show_resource_font_windows)
	{
		uint UID = App->resource_manager->ResourceWindows(R_FONT);
		if (UID == -1)
		{
			show_resource_font_windows = false;
		}
		else if (UID != 0)
		{
			Resource* new_resource = App->resource_manager->Get(UID);
			bool update = true;

			if (text != nullptr)
			{

				if (new_resource->GetOriginalFile().compare(text->GetOriginalFile()) == 0)
				{
					update = false;
				}
				else
				{
					text->UnLoadInMemory();
					text = (ResourceFont*)new_resource;

				}
			}
			else
			{
				text = (ResourceFont*)new_resource;

			}
			if (update)
			{
				text->LoadInMemory();
			}
			show_resource_font_windows = false;
			ImGui::CloseCurrentPopup();
		}
	}
}


uint ComponentText::GetID()
{

	return	(text != nullptr)? id:-1;
}
void ComponentText::FreeFont()
{
	//SDL_FreeSurface(s_font);
	glDeleteTextures(1, &id);
}
void ComponentText::UpdateText()
{
	if (!text->font ||text_str.empty())
		return;
	else if (s_font != NULL && text_str.empty())
	{
		FreeFont();
		return;
	}
	if (s_font != NULL)
	{
		FreeFont();
	}
	update_text = true;

	s_font = TTF_RenderText_Blended(text->font, text_str.c_str(), SDL_Color{(Uint8)(color.x*255), (Uint8)(color.y*255),(Uint8)(color.z*255), (Uint8)(color.w*255) });

	GLuint texture;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s_font->w, s_font->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s_font->pixels);
	SetRect(0.0f, 0.0f, s_font->w, s_font->h);

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(s_font);



}

const TextureRect ComponentText::GetRect() const
{
	return text_rect;
}

void ComponentText::SetUpdateText(bool value)
{
	update_text = value;
}

int ComponentText::GetMaxInput() const
{
	return max_input;
}

bool ComponentText::GetUpdateText() const
{
	return update_text;
}

void ComponentText::SetRect(float x, float y, float width, float height)
{
	text_rect.x = x;
	text_rect.y = y;
	text_rect.width = width;
	text_rect.height = height;
}


void ComponentText::SetString(std::string input)
{
	text_str = input;
	UpdateText();
}

bool ComponentText::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	if (text != nullptr)
	{
		config.SetInt(text->GetResourceType(), "ResourceType");
		config.SetInt(text->GetUID(), "Resource UID");
		config.SetInt(text->size, "Font Size");
		config.SetString(input_text, "InputText");
		config.SetString(text_str, "TextStr");

	}
	config.SetInt(max_input, "Max Input");

	config.SetBool(enable, "Enable");
	return ret;
}

bool ComponentText::LoadComponent(const JSONConfig & config)
{
	bool ret = true;

	if (config.GetInt("ResourceType") != 0)
	{
		text = (ResourceFont*)App->resource_manager->Get(config.GetInt("Resource UID"));
		if (text != nullptr)
		{
			text->size=config.GetInt("Font Size");
			input_text=	config.GetString( "InputText");
			text_str=config.GetString( "TextStr");
			text->LoadInMemory();
			UpdateText();
		}
	}
	max_input=config.GetInt("Max Input");
	enable = config.GetBool("Enable");
	return ret;
}
