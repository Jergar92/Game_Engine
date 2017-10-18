#include "ComponentTransform.h"
#include "Globals.h"
#include "imgui\imgui.h"


ComponentTransform::ComponentTransform(GameObject* my_go) :Component(my_go)
{
	component_name = "Transform";
	type = TRANSFORM;
}


ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::SetTransform(float3 set_scale, Quat set_rotation, float3 set_position)
{
	scale = set_scale;


	rotation = set_rotation;
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;

	position = set_position;

	UpdateMatrix();


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
		ImGui::DragFloat3("Position##transform_position", &position.x, 3);
		
		float3 tmp = gui_rotation;
		if (ImGui::DragFloat3("Rotation##transform_rotation", &tmp.x, 3))
			SetRotation(tmp);

		
		if (ImGui::DragFloat3("Scale##transform_scale", &scale.x, 3))
			SetScale(scale);

		ImGui::TreePop();

	}
}

void ComponentTransform::UpdateMatrix()
{
	transform_matrix = float4x4::FromTRS(position,rotation,scale);
	transform_matrix_inverse = transform_matrix.Transposed();
}

float4x4 ComponentTransform::GetInverseMatrix()const
{
	return transform_matrix_inverse;
}

void ComponentTransform::SetScale(float3 scale)
{
	this->scale = scale;
	
	UpdateMatrix();

}

void ComponentTransform::SetRotation(float3 rotation_angles)
{
	float3 delta = (rotation_angles - gui_rotation) * DEGTORAD;
	Quat rotate_rotation = Quat::FromEulerXYZ(delta.x,delta.y,delta.z);

	rotation = rotation * rotate_rotation;
	gui_rotation = rotation_angles;
	UpdateMatrix();
	
}
