#include "ComponentRectTransform.h"
#include "Globals.h"
#include "imgui\imgui.h"


ComponentRectTransform::ComponentRectTransform(GameObject* my_go, float3 scale, Quat rotation, float3 position) :Component(my_go), scale(scale), rotation(rotation), position(position)
{
	component_name = "RectTransform";
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;

	type = RECT_TRANSFORM;
}


ComponentRectTransform::~ComponentRectTransform()
{
}

void ComponentRectTransform::SetTransform(float3 set_scale, Quat set_rotation, float3 set_position)
{
	scale = set_scale;


	rotation = set_rotation;
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;

	position = set_position;

	UpdateMatrix();


}

void ComponentRectTransform::GuiUpdate()
{
}

void ComponentRectTransform::InspectorUpdate()
{
	uint flags = ImGuiTreeNodeFlags_DefaultOpen;

	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags);

	if (node_open)
	{
		rotation.ToEulerXYX();

		if (ImGui::DragFloat3("Position##transform_position", &position.x, 3))
			SetPosition(position);

		float3 tmp = gui_rotation;
		if (ImGui::DragFloat3("Rotation##transform_rotation", &tmp.x, 3))
			SetRotation(tmp);


		if (ImGui::DragFloat3("Scale##transform_scale", &scale.x, 3))
			SetScale(scale);

		ImGui::TreePop();

	}
}

void ComponentRectTransform::UpdateMatrix()
{
	transform_matrix = float4x4::FromTRS(position, rotation, scale);

	if (my_go->GetPartent() != nullptr)
	{
		global_transform_matrix = my_go->GetPartent()->GetGlobalMatrix() * transform_matrix;
	}
	else
	{
		global_transform_matrix = transform_matrix;
	}

	global_transform_matrix_transposed = global_transform_matrix.Transposed();

	my_go->UpdateBoundingBox();

	for (uint i = 0; i < my_go->components.size(); i++)
	{
		my_go->components[i]->OnUpdateMatrix(global_transform_matrix);
	}
	for (uint i = 0; i < my_go->childs.size(); i++)
	{
		my_go->childs[i]->UpdateMatrix();
	}
}

float4x4 ComponentRectTransform::GetTransposedMatrix()const
{
	return global_transform_matrix_transposed;
}

float4x4 ComponentRectTransform::GetGlobalMatrix() const
{
	return global_transform_matrix;
}

float4x4 ComponentRectTransform::GetInverseMatrix()const
{
	return transform_matrix_transposed;
}

void ComponentRectTransform::SetScale(float3 scale)
{
	this->scale = scale;
	UpdateMatrix();
}

void ComponentRectTransform::SetRotation(float3 rotation_angles)
{
	float3 delta = (rotation_angles - gui_rotation) * DEGTORAD;
	Quat rotate_rotation = Quat::FromEulerXYZ(delta.x, delta.y, delta.z);

	rotation = rotation * rotate_rotation;
	gui_rotation = rotation_angles;
	UpdateMatrix();

}

void ComponentRectTransform::SetPosition(float3 Position)
{
	this->position = position;
	UpdateMatrix();

}

bool ComponentRectTransform::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetFloat3(position, "Translation");
	config.SetQuaternion(rotation, "Rotation");
	config.SetFloat3(scale, "Scale");

	config.SetBool(enable, "Enable");

	//save the path of the mesh.frog
	return ret;
}

bool ComponentRectTransform::LoadComponent(const JSONConfig & config)
{
	bool ret = true;

	position = config.GetFloat3("Translation");
	rotation = config.GetQuaternion("Rotation");
	scale = config.GetFloat3("Scale");
	UpdateMatrix();

	enable = config.GetBool("Enable");

	return ret;
}