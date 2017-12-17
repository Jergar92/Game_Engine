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
#include "ComponentRectTransform.h"
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128


ComponentPanel::ComponentPanel(GameObject * my_go) : ComponentInteractive(my_go)
{

	component_name = "Panel";
	type = CANVAS_IMDRAG;
	canvas = FindMyCanvas();
	if(canvas!=nullptr)
	canvas->interactive_array.push_back((ComponentInteractive*)this);
}

ComponentPanel::~ComponentPanel()
{

}


void ComponentPanel::Update(float dt)
{
	if (center)
	{
		if (canvas != nullptr)
		{
			transform->SetPosition(float3((canvas->GetCanvasData().size.x * 0.5) - (transform->GetWidth() * 0.5), (canvas->GetCanvasData().size.y * 0.5) - (transform->GetHeight() * 0.5), transform->value.z));
		}
	}

}

bool ComponentPanel::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");

	config.SetBool(center, "Center");

	config.SetBool(is_dragable, "Dragable");
	config.SetBool(enable, "Enable");

	return ret;
}

bool ComponentPanel::LoadComponent(const JSONConfig & config)
{
	if (canvas != nullptr)
	{
		canvas = FindMyCanvas();
		if (canvas != nullptr)
			canvas->interactive_array.push_back((ComponentInteractive*)this);
	}
	center = config.GetBool("Center");

	is_dragable = config.GetBool("Dragable");
	enable = config.GetBool("Enable");
	return true;
}

void ComponentPanel::CleanUp()
{
	if (canvas != nullptr)
	{
		canvas->EraseInteractiveElement(this);
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
		ImGui::Checkbox("Set Center", &center);
		ImGui::TreePop();


	}
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
