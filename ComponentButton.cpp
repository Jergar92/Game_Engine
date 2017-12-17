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
#include "EventSystem.h"
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128
ComponentButton::ComponentButton(GameObject* my_go) : ComponentInteractive(my_go)
{
	component_name = "Button";
	type = CANVAS_BUTTON;
	canvas = FindMyCanvas();
	if (canvas != nullptr)
	canvas->interactive_array.push_back((ComponentInteractive*)this);
	texture = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);
	functions[0]="Fade Parent";
	functions[1] = "Do nothing1";
	functions[2] = "Do nothing2";

};



ComponentButton::~ComponentButton()
{
	
}

void ComponentButton::Update(float dt)
{

}
void ComponentButton::CleanUp()
{
	if (canvas != nullptr)
	{

	}
}
bool ComponentButton::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetInt((over_texture != nullptr) ? over_texture->GetResourceType() : 0, "ResourceOverType");
	config.SetInt((click_texture != nullptr) ? click_texture->GetResourceType() : 0, "ResourceClickType");

	if (over_texture != nullptr)
	{
		config.SetInt(over_texture->GetUID(), "Resource Over UID");
	}
	if (click_texture != nullptr)
	{
		config.SetInt(click_texture->GetUID(), "Resource Click UID");
	}
	config.SetBool(enable, "Enable");
	return ret;
}

bool ComponentButton::LoadComponent(const JSONConfig & config)
{
	if (canvas != nullptr)
	{
		canvas = FindMyCanvas();
		if (canvas != nullptr)
			canvas->interactive_array.push_back((ComponentInteractive*)this);
	}

	texture = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);
	if (config.GetInt("ResourceOverType") != 0)
	{
		over_texture = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource Over UID"));
		if (over_texture != nullptr)
		{
			over_texture->LoadInMemory();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	if (config.GetInt("ResourceClickType") != 0)
	{
		click_texture = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource Click UID"));
		if (click_texture != nullptr)
		{
			click_texture->LoadInMemory();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	enable = config.GetBool("Enable");
	return true;
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
		//ImGui::Checkbox("Enable Drag", &is_dragable);
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
		ImGui::Text("Function Selection");
		for (int i = 0; i < functions.size(); i++)
		{
			ImGui::RadioButton(functions[i], &function_selection, i);
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

void ComponentButton::StartFunciton(int event_num)
{
	for (std::map<int, const char*>::const_iterator it = functions.begin(); it != functions.end(); it++)
	{
		if (it->first == event_num)
			EventS->CallEvent(it->second);
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
	StartFunciton(function_selection);
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


