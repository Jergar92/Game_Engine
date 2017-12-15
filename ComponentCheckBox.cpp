#include "ComponentCheckBox.h"
#include "GameObject.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "ComponentCanvas.h"
#include "ResourceTexture.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "ComponentImage.h"

ComponentCheckBox::ComponentCheckBox(GameObject* my_go) : ComponentInteractive(my_go)
{
	component_name = "CheckBox";
	type = CANVAS_CHECKBOX;
	canvas = FindMyCanvas();

	canvas->interactive_array.push_back((ComponentInteractive*)this);
	check = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);

	InspectorCheck(&empty);
	InspectorCheck(&checked);
	id_active = checked->GetID();
	id_unactive = checked->GetID();
}

ComponentCheckBox::~ComponentCheckBox()
{
}

void ComponentCheckBox::Update(float dt)
{
	canvas->UpdateInteractive();

	if (actived)
	{
		check->ChangeImage(id_unactive);
		actived = false;
	}
	else
	{
		check->ChangeImage(id_active);
		actived = true;
	}
	
}

void ComponentCheckBox::Click()
{
	switch (actived)
	{
		case true:

			return;
		case false:
	
			return;
		default:
			break;
	}
	actived = !actived;
}

void ComponentCheckBox::InspectorCheck(ResourceTexture** state)
{
	bool ret = false;
	uint UID = App->resource_manager->ResourceWindows(R_TEXTURE);
	if (UID == -1)
	{
		return;
	}
	else if (UID != 0)
	{
		Resource* new_resource = App->resource_manager->Get(UID);
		bool update = true;

		if (*state != nullptr)
		{

			if (new_resource->GetOriginalFile().compare((*state)->GetOriginalFile()) == 0)
			{
				update = false;
			}
			else
			{
				(*state)->UnLoadInMemory();
				*state = (ResourceTexture*)new_resource;

			}
		}
		else
		{
			*state = (ResourceTexture*)new_resource;
		}
		if (update)
		{
			(*state)->LoadInMemory();
		}

		ImGui::CloseCurrentPopup();
	}

}

void ComponentCheckBox::Idle()
{
}

void ComponentCheckBox::Hover()
{
}

void ComponentCheckBox::Down()
{
}
