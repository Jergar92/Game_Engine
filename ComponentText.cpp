#include "ComponentText.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "ResourceFont.h"
#include "imgui/imgui.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

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

void ComponentText::SetString(std::string input)
{
	text_str = input;
}
