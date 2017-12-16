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
	functions[0] = "Change Vsync";
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
			EventS->CallEvent(it->second, actived);
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
}
