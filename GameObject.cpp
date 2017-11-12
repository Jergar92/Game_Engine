#include "Application.h"
#include "GameObject.h"
#include "imgui\imgui.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleScene.h"
#include "ModuleEditorWindows.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ResourceMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"

#define MAX_NAME 20
GameObject::GameObject(float3 scale, Quat rotation, float3 position) :name("Game Object"),scale(scale), rotation(rotation), position(position)
{
	UID = App->GenerateRandom();
	input_name = name;
	gui_rotation = rotation.ToEulerXYZ() * RADTODEG;
	UpdateMatrix();

}

GameObject::GameObject(GameObject * parent, float3 scale, Quat rotation, float3 position) :name("Game Object"),scale(scale), rotation(rotation), position(position)
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
		RELEASE(item);

	}

	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->CleanUp();
		RELEASE(item);

	}
	parent = nullptr;

}
void GameObject::PreUpdate(float dt)
{
	
}
void GameObject::Update(float dt)
{

	if (!enable)
		return;

	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if (item->isEnable())
			item->Update(dt);
	}
	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->Update(dt);
	}

	if (show_bounding_box)
	{
		RenderBoundingBoxAABB();
		RenderBoundingBoxOBB();
	}
}

void GameObject::PostUpdate(float dt)
{
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if (item->ToDelete())
		{
			if (RemoveComponent(item->type,i))
			{
				LOG("Remove Component Complete");
				break;
			}
			else
			{
				LOG("Remove Component Fail");
			}
		}
	}
	
	//With this setup you can't delete the scene
	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		if (item->to_delete)
		{

			if (RemoveGO(item))
			{
				LOG("Remove GameObject Complete");
			}
			else
			{
				LOG("Remove GameObject Fail");
			}

		}
		else
			item->PostUpdate(dt);
	}

}

void GameObject::GuiUpdate()
{
	bool node_open = false;
	ImGuiWindowFlags tree_flags = 0;

	//Set color white enable go grey disabled go
	if (childs.empty())
		tree_flags |= ImGuiTreeNodeFlags_Leaf;
	
	if (App->editor_window->GetSelectedGameObject() == this)
	{
		tree_flags |= ImGuiTreeNodeFlags_Selected;
	}

	//change color to gray
	if (!enable)	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
	char name_id[40];
	sprintf_s(name_id, 40, "%s##%i", name.c_str(), UID);
	node_open = ImGui::TreeNodeEx(name_id, tree_flags);
	//reset color
	if (!enable)	ImGui::PopStyleColor();


	//Set item selected->InspectorUpdate
	if (ImGui::IsItemClicked())
		App->editor_window->SetSelectedGameObject(this);
	ImGui::PushID(name_id);
		if (ImGui::BeginPopupContextItem("go_options"))
		{	//Scene GO protection
			if (parent != nullptr)
			{
				if (ImGui::Button("Delete Game Object"))
				{
					ToDelete();
					ImGui::CloseCurrentPopup();
				}
			}
			if (ImGui::Button("Create Game Object"))
			{
				CreateChild();
				ImGui::CloseCurrentPopup();

			}
			ImGui::EndPopup();
		}
		ImGui::PopID();


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
	if (gui_static)
		OpenStaticQuestion();
	//Start draw Elements 
	bool node_open = ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen);
	if (node_open)
	{
		rotation.ToEulerXYX();
		if (ImGui::DragFloat3("Position##transform_position", &position.x, 0.1f))
			SetPosition(position);
		float3 tmp = gui_rotation;
		if (ImGui::DragFloat3("Rotation##transform_rotation", &tmp.x, 0.1f))
			SetRotation(tmp);
		if (ImGui::DragFloat3("Scale##transform_scale", &scale.x, 0.01f))
			SetScale(scale);
		ImGui::TreePop();
	}

	ImGui::Checkbox("Bounding Box OBB##show_bb", &show_bounding_box);

	for (uint i = 0; i < components.size(); i++)
	{
		ImGui::Separator();
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

	UID = data.GetInt("UID");

	parent_UID = data.GetInt("ParentUID");


	SetName(data.GetString("Name"));
	position = data.GetFloat3("Translation");
	rotation = data.GetQuaternion("Rotation");
	scale = data.GetFloat3("Scale");
	UpdateMatrix();

	uint size = data.GetArraySize("Components");
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = data.SetFocusArray("Components", i);
		Component*item = CreateComponent((ComponentType)config_item.GetInt("Type"));
		item->LoadComponent(config_item);
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

GameObject * GameObject::CreateChild()
{
	GameObject* ret = new GameObject(this);
	return ret;
}

Component * GameObject::CreateComponent(ComponentType type)
{
	Component* item = nullptr;
	if (HaveComponent(type))
	{
		LOG("This GameObject have that component already");
		return item;
	}
	switch (type)
	{
	case MESH:
		
		item = new ComponentMesh(this);
		break;
	case MESH_RENDER:
	{
		if (!HaveComponent(MESH))
		{
			LOG("Add Component mesh")
			//Force the creation of mesh if we want a mesh_renderer
			CreateComponent(MESH);
		}
		item = new ComponentMeshRenderer(this);
	}
		break;
	case CAMERA:
		item = new ComponentCamera(this);
		break;
	default:
		break;
	}
	if (item != nullptr)
	{
		AddComponent(item);
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
bool GameObject::RemoveComponent(ComponentType type,int position)
{
	Component* item = FindComponent(type);

	if (type == MESH)
	{
		if (HaveComponent(MESH_RENDER))
		{
			LOG("You cant remove a component mesh if you have a component mesh renderer");
			item->to_delete = false;
			return false;
		}
	}
	components.erase(components.begin() + position);
	RELEASE(item);
	LOG("Remove a component!");
	return true;
}
bool GameObject::RemoveGO(GameObject * to_remove)
{
	GameObject* ret = nullptr;
	
	for (int i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];

		if (item == to_remove)
		{
			childs.erase(childs.begin() + i);
			return true;
		}
	}
	return false;
}
bool GameObject::HaveComponent(ComponentType type) const
{
	Component* ret = nullptr;
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];

		if (item->type == type)
		{
			return true;
		}
	}
	return false;
}

void GameObject::ToDelete()
{
	to_delete = true;
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

	global_bounding_box_OBB = global_bounding_box_AABB.Transform(global_transform_matrix);
	
	indentity_bounding_box_AABB = global_bounding_box_AABB;
	indentity_bounding_box_AABB.TransformAsAABB(global_transform_matrix);
	is_bounding_box_transformed = true;
	
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnUpdateMatrix(global_transform_matrix);
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

float4x4 GameObject::GetGlobalMatrix() const
{
	return global_transform_matrix;
}

GameObject * GameObject::GetPartent() const
{
	return parent;
}

OBB GameObject::GetBoundingBoxOBB() const
{
	return global_bounding_box_OBB;
}

AABB GameObject::GetBoundingBoxAABB() const
{
	return global_bounding_box_AABB;
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

void GameObject::SetPosition(float3 position)
{
	this->position = position;
	UpdateMatrix();

}

void GameObject::GenerateBoudingBox()
{
	ComponentMesh* mesh = (ComponentMesh*)FindComponent(MESH);
	global_bounding_box_AABB.SetNegativeInfinity();
	if (mesh != nullptr)
	{
		for (int i = 0; i < mesh->GetVertices().size(); i++)
		{
			global_bounding_box_AABB.Enclose(mesh->GetVertices()[i].position);
		}
	}

	if (!childs.empty())
	{
		for (int i = 0; i < childs.size(); i++)
		{
		global_bounding_box_AABB.Enclose(childs[i]->indentity_bounding_box_AABB);
		}
	}

	UpdateMatrix();
	if (parent != nullptr)
	{
		parent->GenerateBoudingBox();
	}
}


void GameObject::SetAABB(const AABB set_bounding_box)
{
	indentity_bounding_box_AABB = set_bounding_box;
}

void GameObject::RenderBoundingBoxAABB()
{
	glBegin(GL_LINES);
	if (!is_bounding_box_transformed)
	{
		for (uint i = 0; i < 12; i++)
		{
			glVertex3f(global_bounding_box_AABB.Edge(i).a.x, global_bounding_box_AABB.Edge(i).a.y, global_bounding_box_AABB.Edge(i).a.z);
			glVertex3f(global_bounding_box_AABB.Edge(i).b.x, global_bounding_box_AABB.Edge(i).b.y, global_bounding_box_AABB.Edge(i).b.z);
		}
	}
	for (uint i = 0; i < 12; i++)
	{
		glVertex3f(indentity_bounding_box_AABB.Edge(i).a.x, indentity_bounding_box_AABB.Edge(i).a.y, indentity_bounding_box_AABB.Edge(i).a.z);
		glVertex3f(indentity_bounding_box_AABB.Edge(i).b.x, indentity_bounding_box_AABB.Edge(i).b.y, indentity_bounding_box_AABB.Edge(i).b.z);
	}
	glEnd();

}

void GameObject::RenderBoundingBoxOBB()
{
	glBegin(GL_LINES);
	for (uint i = 0; i < 12; i++)
	{
		glVertex3f(global_bounding_box_OBB.Edge(i).a.x, global_bounding_box_OBB.Edge(i).a.y, global_bounding_box_OBB.Edge(i).a.z);
		glVertex3f(global_bounding_box_OBB.Edge(i).b.x, global_bounding_box_OBB.Edge(i).b.y, global_bounding_box_OBB.Edge(i).b.z);
	}
	glEnd();
}

