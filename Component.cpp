#include "Component.h"
#include "imgui/imgui.h"


Component::Component(GameObject* my_go):enable(true)
{
	SetMyGO(my_go);
}


Component::~Component()
{
}

void Component::Enable()
{
	enable = true;

}
void Component::OnPlay()
{
}
void Component::OnStop()
{
}
void Component::LinkComponent()
{
}
void Component::CleanUp()
{
}

void Component::Update(float dt)
{
}

void Component::GuiUpdate()
{
}

void Component::InspectorUpdate()
{
	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox| ImGuiTreeNodeFlags_Leaf;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);
	ImGui::TreePop();
}



bool Component::SaveComponent(JSONConfig& data)const
{
	return true;
}

bool Component::LoadComponent(const JSONConfig& data)
{
	return true;
}

void Component::OnUpdateMatrix(const float4x4 & matrix)
{
}


void Component::Disable()
{
	enable = false;
}

void Component::DeleteComponent()
{
	to_delete= true;
}

bool Component::ToDelete() const
{
	return to_delete;
}

bool Component::isEnable()
{
	return enable==true;
}

void Component::SetMyGO(GameObject * get)
{
	my_go = get;
}
