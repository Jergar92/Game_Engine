#include "ComponentTransform.h"
#include "imgui\imgui.h"


ComponentTransform::ComponentTransform(GameObject* my_go) :Component(my_go)
{
	component_name = "Transform";
}


ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::SetTransform(float3 set_scale, Quat set_rotation, float3 set_position)
{
	scale = set_scale;


	rotation = set_rotation;
	gui_rotation = rotation.ToEulerXYZ();

	position = set_position;
}

void ComponentTransform::GuiUpdate()
{
}

void ComponentTransform::InspectorUpdate()
{
	bool node_open = ImGui::TreeNode(component_name.c_str());

	if (node_open)
	{
		rotation.ToEulerXYX();
		ImGui::InputFloat3("Position##transform_position", &position.x, 3);
		ImGui::InputFloat3("Rotation##transform_rotation", &gui_rotation.x, 3);
		ImGui::InputFloat3("Scale##transform_scale", &scale.x, 3);

		ImGui::TreePop();

	}
}
