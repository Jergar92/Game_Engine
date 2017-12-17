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
		if (block)
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

		rotation.ToEulerXYX();

		if (ImGui::DragFloat3("Position##transform_position", &value.x, 1))
			SetPosition(value);

		float3 tmp = gui_rotation;
		if (ImGui::DragFloat3("Rotation##transform_rotation", &tmp.x, 1))
			SetRotation(tmp);


		if (ImGui::DragFloat3("Scale##transform_scale", &scale.x, 1))
			SetScale(scale);

		ImGui::PushItemWidth(120);
		if (ImGui::DragFloat("w##transform_width", &width, 1))
			SetWidth(width);

		ImGui::SameLine();

		if (ImGui::DragFloat("h##transform_height", &height, 1))
			SetHeight(height);
		ImGui::PopItemWidth();

		if (block)
			ImGui::PopStyleVar();
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

float ComponentRectTransform::Getdepth() const
{
	return depth;
}

float3 ComponentRectTransform::GetSouthWest() const
{
	//negative x, negative y  
	return float3(0,0,0);
}

float3 ComponentRectTransform::GetNorthWest() const
{
	//negative x, positive y
	return float3(0,height,0);
}

float3 ComponentRectTransform::GetSouthEast() const
{
	//positive x, positive y
	return float3(width,0,0);
}

float3 ComponentRectTransform::GetNorthEeast() const
{
	//positive x, negative y
	return float3(width,height,0);
}

float4x4 ComponentRectTransform::GetInverseMatrix()const
{
	return transform_matrix_transposed;
}

void ComponentRectTransform::SetBlock(bool set_block)
{
	block = set_block;
}

float ComponentRectTransform::GetWidth() const
{

	return width ;

}

float ComponentRectTransform::GetHeight() const
{
	
	return height;

}

float ComponentRectTransform::GetDepth() const
{
	return depth;
}


float2 ComponentRectTransform::GetPivot() const
{

	return pivot;

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

void ComponentRectTransform::SetPosition(float3 position)
{
	value = { position.x,position.y, depth = position.z };
	position.z = 0;
	this->position = position;
	UpdateMatrix();
}

void ComponentRectTransform::SetWidth(float set_width)
{

	width = set_width;

}



void ComponentRectTransform::SetHeight(float set_height)
{

	height = set_height;
}



bool ComponentRectTransform::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetFloat3(position, "Translation");
	config.SetFloat3(value, "Value");

	config.SetQuaternion(rotation, "Rotation");
	config.SetFloat3(scale, "Scale");

	config.SetFloat(width, "Width");
	config.SetFloat(height, "Height");




	config.SetBool(enable, "Enable");

	//save the path of the mesh.frog
	return ret;
}

bool ComponentRectTransform::LoadComponent(const JSONConfig & config)
{
	bool ret = true;

	position = config.GetFloat3("Translation");

	value = config.GetFloat3("Value");
	depth = value.z;
	rotation = config.GetQuaternion("Rotation");
	scale = config.GetFloat3("Scale");
	width = config.GetFloat("Width");
	height = config.GetFloat("Height");

	UpdateMatrix();

	enable = config.GetBool("Enable");

	return ret;
}