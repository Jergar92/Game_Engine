#include "ComponentPanel.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "GameObject.h"
#include "ResourceTexture.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "ComponentInteractive.h"
#include "ComponentCanvas.h"
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128


ComponentPanel::ComponentPanel(GameObject * my_go) : ComponentInteractive(my_go)
{

	component_name = "Panel";
	type = CANVAS_IMDRAG;
	canvas = FindMyCanvas();
	canvas->interactive_array.push_back((ComponentInteractive*)this);
}

ComponentPanel::~ComponentPanel()
{

}


void ComponentPanel::Update(float dt)
{
}

bool ComponentPanel::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetInt((image != nullptr) ? image->GetResourceType() : 0, "ResourceType");
	if (image != nullptr)
	{
		config.SetInt(image->GetUID(), "Resource UID");
	}

	config.SetBool(enable, "Enable");
	return ret;
}

bool ComponentPanel::LoadComponent(const JSONConfig & config)
{
	if (config.GetInt("ResourceType") != 0)
	{
		image = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource UID"));
		if (image != nullptr)
		{
			image->LoadInMemory();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	enable = config.GetBool("Enable");
	return true;
}

void ComponentPanel::ChangeImage(uint ID)
{
	if (ID == 0)
	{
		tmp_id = image->GetID();
	}
	else
	{
		tmp_id = ID;
	}

}

void ComponentPanel::InspectorUpdate()
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
		ImGui::Checkbox("Enable Drag", &is_dragable);
		ImGui::TreePop();
	}
}

const ResourceTexture * ComponentPanel::GetImage() const
{
	return image;
}

void ComponentPanel::EqualizeUv()
{
	uv0.x = world_uv0.x / image->GetWidth();
	uv0.y = world_uv0.y / image->GetHeight();
	uv1.x = world_uv1.x / image->GetWidth();
	uv1.y = world_uv1.y / image->GetHeight();
}

void ComponentPanel::EqualizeWorldUv()
{
	world_uv0.x = uv0.x * image->GetWidth();
	world_uv0.y = uv0.y* image->GetHeight();
	world_uv1.x = uv1.x* image->GetWidth();
	world_uv1.y = uv1.y* image->GetHeight();
}

void ComponentPanel::SetWorldUvValues()
{
	world_uv1.x = image->GetWidth();
	world_uv1.y = image->GetHeight();

}

uint ComponentPanel::GetImageID() const
{
	return (image != nullptr) ? tmp_id : -1;
}

float2 ComponentPanel::GetUV0() const
{
	return uv0;
}
float2 ComponentPanel::GetUV1() const
{
	return uv1;
}

void ComponentPanel::Idle()
{
}

void ComponentPanel::Hover()
{
}

void ComponentPanel::Down()
{
}
