#include "ComponentCheckBox.h"
#include "GameObject.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "ComponentCanvas.h"
#include "ResourceTexture.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "ComponentImage.h"
#include "EventSystem.h"
ComponentCheckBox::ComponentCheckBox(GameObject* my_go) : ComponentInteractive(my_go)
{
	component_name = "CheckBox";
	type = CANVAS_CHECKBOX;
	canvas = FindMyCanvas();

	canvas->interactive_array.push_back((ComponentInteractive*)this);
	box = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);
	functions[0] = "Vsync";
	functions[1] = "Change Cullface";
	InspectorCheck(&pressed);
}

ComponentCheckBox::~ComponentCheckBox()
{
}

void ComponentCheckBox::Update(float dt)
{
}

void ComponentCheckBox::Click()
{
	if (on_execution)
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
}
bool ComponentCheckBox::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetInt((hover != nullptr) ? hover->GetResourceType() : 0, "ResourceHoverType");
	config.SetInt((pressed != nullptr) ? pressed->GetResourceType() : 0, "ResourcePressedType");

	if (hover != nullptr)
	{
		config.SetInt(hover->GetUID(), "Resource Hover UID");
	}
	if (pressed != nullptr)
	{
		config.SetInt(pressed->GetUID(), "Resource Pressed UID");
	}

	
	config.SetBool(actived, "Actived");

	config.SetBool(enable, "Enable");
	return ret;
}

bool ComponentCheckBox::LoadComponent(const JSONConfig & config)
{
	if (canvas != nullptr)
	{
		canvas = FindMyCanvas();
		if (canvas != nullptr)
			canvas->interactive_array.push_back((ComponentInteractive*)this);
	}

	box = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);
	if (config.GetInt("ResourceHoverType") != 0)
	{
		hover = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource Hover UID"));
		if (hover != nullptr)
		{
			hover->LoadInMemory();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	if (config.GetInt("ResourcePressedType") != 0)
	{
		pressed = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource Pressed UID"));
		if (pressed != nullptr)
		{
			pressed->LoadInMemory();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	activated = config.GetBool("Actived");
	enable = config.GetBool("Enable");
	return true;
}
void ComponentCheckBox::CleanUp()
{
	if (canvas != nullptr)
	{
		canvas->EraseInteractiveElement(this);
	}
}
void ComponentCheckBox::InspectorUpdate()
{
	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);
	if (ImGui::BeginPopupContextItem("go_options"))
	{
		if (ImGui::Button("Delete Component"))
		{
			DeleteComponent();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	if (node_open)
	{

		if (ImGui::Button("Select Empty checkbox Texture"))
		{
			hover_text = true;

		}

		if (ImGui::Button("Select pressed checkbox Texture"))
		{
			active_text = true;
		}
		ImGui::Text("Function Selection");
		for (int i = 0; i < functions.size(); i++)
		{
			ImGui::RadioButton(functions[i], &function_selection, i);
		}
		ImGui::TreePop();
	}

	if (active_text || hover_text)
	{
		bool check = false;
		if (active_text)
		{
			check = InspectorCheck(&pressed);
			if (check)
				pressed_window = false;
		}

		if (hover_text)
		{
			check = InspectorCheck(&hover);
			if (check)
				pressed_window = false;
		}

		if (pressed_window)
		{
			check = InspectorCheck(&pressed);
			if (check)
				pressed_window = false;
		}
	}
}
void ComponentCheckBox::StartFunciton(int event_num)
{
	for (std::map<int, const char*>::const_iterator it = functions.begin(); it != functions.end(); it++)
	{
		if (it->first == event_num)
			EventS->CallEvent(it->second, activated);
	}
}
bool ComponentCheckBox::InspectorCheck(ResourceTexture** status)
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
		active_text = false;
		hover_text = false;

		ImGui::CloseCurrentPopup();
	}
	return ret;

}

void ComponentCheckBox::Idle()
{
	uint id = 0;
	if (activated && pressed != nullptr)
	{ 
		id = pressed->GetID();
	}
	box->ChangeImage(id);
}

void ComponentCheckBox::Hover()
{

}

void ComponentCheckBox::Down()
{
	uint id = 0;
	activated = !activated;
	if (activated && pressed != nullptr)
	{
		id = pressed->GetID();
	}
	box->ChangeImage(id);
	StartFunciton(function_selection);
}
