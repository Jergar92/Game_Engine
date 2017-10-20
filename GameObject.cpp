#include "Application.h"
#include "GameObject.h"
#include "imgui\imgui.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleScene.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"
#define MAX_NAME 20
GameObject::GameObject(float3 scale, Quat rotation, float3 position) :scale(scale),rotation(rotation),position(position)
{
	name = "Scene";
	input_name = name;
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;
	UpdateMatrix();

}

GameObject::GameObject(GameObject * parent, float3 scale, Quat rotation,float3 position) :scale(scale), rotation(rotation), position(position)
{

	SetParent(parent);
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;
	UpdateMatrix();

}




GameObject::~GameObject()
{
}
void GameObject::CleanUp()
{
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		item->CleanUp();
	}

	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->CleanUp();
	}
	parent = nullptr;
}
void GameObject::Update()
{
	//Get Transform

	glPushMatrix();
	glMultMatrixf((float*)&GetInverseMatrix());
	

	if (!enable)
		return;
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if(item->isEnable())
			item->Update();
	}
	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
			item->Update();

	}

		//Pop Matrix
		glPopMatrix();
	
}

void GameObject::GuiUpdate()
{

	bool node_open = ImGui::TreeNode(name.c_str());

	if (ImGui::IsItemClicked())
	{
		App->scene->SetSelectedGameObject(this);
	}
	if (node_open)
	{
		for (uint i = 0; i < childs.size(); i++)
		{
			GameObject* item = childs[i];
			item->GuiUpdate();
		}
		ImGui::TreePop();

	}
	
}

void GameObject::InspectorUpdate()
{

	 ImGui::Checkbox("##go_enable", &enable);
	 ImGui::SameLine();
	 
	 if (ImGui::InputText("##go_name", (char*)input_name.c_str(), MAX_NAME, ImGuiInputTextFlags_EnterReturnsTrue))
	 {
		SetName(input_name.c_str());
	 }
	 ImGui::SameLine();

	 ImGui::Checkbox("Static##static_go", &static_go);

	 bool node_open = ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen);


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

	
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		item->InspectorUpdate();
	}	
}

const char * GameObject::GetName()
{
	return name.c_str();
}

void GameObject::SetParent(GameObject * set_parent)
{
	if (set_parent != nullptr)
	{
		parent = set_parent;
		set_parent->SetChild(this);
	}
}

void GameObject::SetChild(GameObject * child)
{
	if (child != nullptr)
	{
		childs.push_back(child);
	}

}

void GameObject::SetName(const char * set_name)
{
	name = set_name;
	input_name = name;
}

void GameObject::AddComponent(Component * component_to_add)
{
	components.push_back(component_to_add);
}

Component * GameObject::CreateComponent(ComponentType type)
{
	Component* item = nullptr;
	switch (type)
	{
	case MESH:
		item = new ComponentMesh(this);
		break;
	case MESH_RENDER:
		item = new ComponentMeshRenderer(this);
		break;
	default:
		break;
	}
	return item;
}

Component* GameObject::FindComponent(ComponentType type, Component * component_to_find)
{
	Component* ret = nullptr;
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];

		if (item->type == type)
		{
			if (item == component_to_find)
			{
				ret = item;
				return item;
			}
		}
	}
	
	return ret;
}

Component* GameObject::FindComponent(ComponentType type)
{
	Component* ret = nullptr;
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];

		if (item->type == type)
		{
			ret = item;
			return item;
		}
	}
	return ret;
}
void GameObject::SetTransform(float3 set_scale, Quat set_rotation, float3 set_position)
{
	scale = set_scale;


	rotation = set_rotation;
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;

	position = set_position;

	UpdateMatrix();


}
void GameObject::UpdateMatrix()
{
	transform_matrix = float4x4::FromTRS(position, rotation, scale);
	transform_matrix_inverse = transform_matrix.Transposed();
}

float4x4 GameObject::GetInverseMatrix()const
{
	return transform_matrix_inverse;
}

void GameObject::SetScale(float3 scale)
{
	this->scale = scale;
	UpdateMatrix();
}

void GameObject::SetRotation(float3 rotation_angles)
{
	float3 delta = (rotation_angles - gui_rotation) * DEGTORAD;
	Quat rotate_rotation = Quat::FromEulerXYZ(delta.x, delta.y, delta.z);

	rotation = rotation * rotate_rotation;
	gui_rotation = rotation_angles;
	UpdateMatrix();

}

void GameObject::SetPosition(float3 Position)
{
	this->position = position;
	UpdateMatrix();

}
