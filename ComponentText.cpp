#include "ComponentText.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "ResourceFont.h"


#include "imgui/imgui.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SDL\include\SDL.h"
#include "SDL_ttf\include\SDL_ttf.h"
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

			if (ImGui::DragInt("Font Size##transform_position", &text->size, 1,0))
			{
				text->UnLoadInMemory();
				text->LoadInMemory();
			}
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

	return	(text != nullptr)? text->id:-1;
}

void ComponentText::UpdateText()
{
	if (text->font == nullptr)
		return;
	s_font = TTF_RenderText_Blended(text->font, text_str.c_str(), SDL_Color{(Uint8)color.x, (Uint8)color.y,(Uint8)color.z, (Uint8)color.w });

	GLuint texture;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s_font->w, s_font->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s_font->pixels);
	
	glBindTexture(GL_TEXTURE_2D, 0);



}


void ComponentText::SetString(std::string input)
{
	text_str = input;
	UpdateText();
}
