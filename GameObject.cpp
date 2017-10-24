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
	bool node_open = false;
	//Set color white enable go grey disabled go
	if (enable)
	{
		node_open = ImGui::TreeNodeEx(name.c_str());
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
		node_open = ImGui::TreeNodeEx(name.c_str());
		ImGui::PopStyleColor();
	}
	//Set item selected->InspectorUpdate
	if (ImGui::IsItemClicked())
		App->scene->SetSelectedGameObject(this);
	
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
	//Enable//Disable Game Object
	 ImGui::Checkbox("##go_enable", &enable);
	 ImGui::SameLine();
	 //Change name
	 if (ImGui::InputText("##go_name", (char*)input_name.c_str(), MAX_NAME, ImGuiInputTextFlags_EnterReturnsTrue))
		SetName(input_name.c_str());	 
	 ImGui::SameLine();
	 //Enable//Disable Static Game Object
	 if (ImGui::Checkbox("Static##static_go", &static_go))
	 	 gui_static = true;
	  if(gui_static)
		 OpenStaticQuestion();	
	//Start draw Elements 
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

void GameObject::OpenStaticQuestion()
{
	if (childs.empty())
	{
		gui_static = false;
		return;
	}
	ImGui::OpenPopup("Change to static?");
	if (ImGui::BeginPopupModal("Change to static?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Change children to?");
		ImGui::Separator();

		static bool children_to = false;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox("Yes", &children_to);
		ImGui::PopStyleVar();

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			if (children_to)
			{
				for (uint i = 0; i < childs.size(); i++)
				{
					GameObject* item = childs[i];
					item->SetStatic(static_go);
				}
			}
			gui_static = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			gui_static = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void GameObject::SetStatic(bool set)
{
	static_go = set;
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

void GameObject::SaveGameObject(JSON_Object * data)
{
	//JSON_Value *root_value = json_value_init_object();
	//JSON_Object *root_object = json_value_get_object(root_value);
	/*
{
"Game Objects":[
{
"UID":1642009359,
"ParentUID":1619219037,
"Name":"RootNode",
"Translation":[0,0,0],
"Scale":[1,1,1],
"Rotation":[0,0,0,1],
"Components":[]
},
	*/
	JSON_Object *root_object = data;
	char *serialized_string = NULL;
	
	json_object_dotset_string(root_object, "Name", name.c_str());
	json_object_dotset_number(root_object, "UUID", UUID);
	if(parent!=nullptr)
		json_object_dotset_number(root_object, "UUID", parent->UUID);
	json_object_dotset_boolean(root_object, "Enable", UUID);
	json_object_dotset_boolean(root_object, "Static", UUID);

	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		item->SaveComponent(root_object);
	}

	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->SaveGameObject(root_object);

	}
	//Send to filesystem//	JSON_Status json_serialize_to_file(const JSON_Value *value, const char *filename);

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
	case CAMERA:
		item = new ComponentCamera(this);
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
