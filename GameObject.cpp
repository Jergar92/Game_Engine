#include "Application.h"
#include "GameObject.h"
#include "imgui\imgui.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleScene.h"
#include "ModuleMenuBar.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"

#define MAX_NAME 20
GameObject::GameObject(float3 scale, Quat rotation, float3 position) :scale(scale),rotation(rotation),position(position)
{
	UID =App->GenerateRandom();
	name = "Scene";
	input_name = name;
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;
	UpdateMatrix();

}

GameObject::GameObject(GameObject * parent, float3 scale, Quat rotation,float3 position) :scale(scale), rotation(rotation), position(position)
{
	UID = App->GenerateRandom();
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
		App->menu_bar->SetSelectedGameObject(this);
	
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
		parent_UID = set_parent->GetUID();
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

void GameObject::LoadGameObject(const JSONConfig & data)
{

	UID=data.GetInt("UID");
	
	parent_UID = data.GetInt("ParentUID");
	

	SetName(data.GetString("Name"));
	position=data.GetFloat3("Translation");
	rotation=data.GetQuaternion("Rotation");
	scale=data.GetFloat3("Scale");
	UpdateMatrix();

	uint size = data.GetArraySize("Components");
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = data.SetFocusArray("Components", i);
		Component*item=CreateComponent((ComponentType)config_item.GetInt("Type"));
		item->LoadComponent(config_item);	
		AddComponent(item);
	}
	//Create and Set all components
}

void GameObject::SaveGameObject(JSONConfig& data)const
{
	JSONConfig config;
	config.SetInt(UID, "UID");
	config.SetInt(parent_UID, "ParentUID");
	config.SetString(name, "Name");
	config.SetFloat3(position, "Translation");
	config.SetQuaternion(rotation, "Rotation");
	config.SetFloat3(scale, "Scale");

	//Set ARRAY components
	config.OpenArray("Components");
	std::vector<Component*>::const_iterator comp_it = components.begin();
	while (comp_it != components.end())
	{
		JSONConfig config_component;
		(*comp_it)->SaveComponent(config_component);
		config.CloseArray(config_component);
		comp_it++;
	}
	data.CloseArray(config);

	std::vector<GameObject*>::const_iterator go_it = childs.begin();
	while (go_it != childs.end())
	{
		config.OpenArray("GameObject");
		(*go_it)->SaveGameObject(data);
		go_it++;
	}



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

Component* GameObject::FindComponent(ComponentType type, Component * component_to_find)const
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

Component* GameObject::FindComponent(ComponentType type)const
{
	Component* ret = nullptr;
	for (int i = 0; i < components.size(); i++)
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
uint GameObject::GetUID() const
{
	return UID;
}
uint GameObject::GetParentUID() const
{

	return parent_UID;

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
	if (parent != nullptr)
	{
		global_transform_matrix = parent->global_transform_matrix * transform_matrix;
	}
	else
	{
		global_transform_matrix = transform_matrix;
	}
	
	global_transform_matrix_transposed = global_transform_matrix.Transposed();
	
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnUpdateMatrix(global_transform_matrix);
		if (components[i]->type == MESH)
		{
			ComponentMesh * mesh = (ComponentMesh*)components[i];
			global_bounding_box = mesh->GetBoundingBox().Transform(global_transform_matrix.Float3x3Part());
		}
	}

	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->UpdateMatrix();
	}
}

float4x4 GameObject::GetTransposedMatrix()const
{
	return global_transform_matrix_transposed;
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
