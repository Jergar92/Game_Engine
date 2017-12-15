#include "ComponentButton.h"
#include "Application.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "ComponentImage.h"
#include "ComponentCanvas.h"
#include "ModuleResourceManager.h"
#include "ResourceTexture.h"
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128
ComponentButton::ComponentButton(GameObject* my_go) : ComponentInteractive(my_go)
{
	component_name = "Button";
	type = CANVAS_BUTTON;
	canvas = FindMyCanvas();
	canvas->interactive_array.push_back((ComponentInteractive*)this);
	texture = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);

};



ComponentButton::~ComponentButton()
{
	
}

void ComponentButton::Update(float dt)
{

}

void ComponentButton::InspectorUpdate()
{
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
		
		/*ShowInfo(OnHove);*/
		if (ImGui::Button("Select Hover Texture##over_texture_texture"))
		{
			over_window = true;

		}

		/*ShowInfo(click_texture);*/
		if (ImGui::Button("Select Click Texture##click_texture_texture"))
		{
			click_window = true;
		}
		ImGui::TreePop();
	}

	if (over_window|| pressed_window|| click_window)
	{
		bool check = false;
		if (over_window)
		{
			check = InspectorCheck(&over_texture);
			if (check)
				over_window = false;
		}

		if (pressed_window)
		{
			check = InspectorCheck(&pressed_texture);
			if (check)
				pressed_window = false;
		}

		if (click_window)
		{
			check = InspectorCheck(&click_texture);
			if (check)
				click_window = false;
		}


		
	}
}

void ComponentButton::ShowInfo(ResourceTexture * texture)
{
	if (texture != nullptr)
	{

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::EndTooltip();
		}

		ImGui::Text("Texture Path:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", over_texture->GetOrignalName().c_str());
		ImGui::PushItemWidth(200);
		ImGui::Text("Image RGBA");
	}
}

void ComponentButton::ButtonFunctionality()
{
	if (last_state != states)
	{
		last_state = states;
		switch (states)
		{
		case IDLE:
			Idle();
			break;

		case HOVER:
			Hover();
			break;

		case DOWN:
			Down();
			break;

		default:
			break;
		}

	}
}

void ComponentButton::Idle()
{
	texture->ChangeImage(0);
}

void ComponentButton::Hover()
{
	uint id = 0;
	if (over_texture != nullptr)
	{
		id = over_texture->GetID();

	}

	texture->ChangeImage(id);
}

void ComponentButton::Down()
{
	uint id = 0;
	if (click_texture != nullptr)
	{
		id = click_texture->GetID();

	}

	texture->ChangeImage(id);
}

bool ComponentButton::InspectorCheck(ResourceTexture** status)
{
	bool ret = false;
	uint UID = App->resource_manager->ResourceWindows(R_TEXTURE);
	if (UID == -1)
	{
		ret = true;
		}
	else if (UID != 0)
	{
		Resource* new_resource = App->resource_manager->Get(UID);
		bool update = true;

		if (*status != nullptr)
		{

			if (new_resource->GetOriginalFile().compare((*status)->GetOriginalFile()) == 0)
			{
				update = false;
			}
			else
			{
				(*status)->UnLoadInMemory();
				*status = (ResourceTexture*)new_resource;

			}
		}
		else
		{
			*status = (ResourceTexture*)new_resource;
		}
		if (update)
		{
			(*status)->LoadInMemory();
		}
		over_window = false;
		pressed_window = false; 
		click_window = false;

		ImGui::CloseCurrentPopup();
	}
	return ret;

}


