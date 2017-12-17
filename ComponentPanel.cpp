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
	if(canvas!=nullptr)
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

	config.SetBool(enable, "Enable");

	config.SetBool(is_dragable, "Dragable");
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
