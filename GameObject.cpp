#include "Application.h"
#include "GameObject.h"
#include "imgui\imgui.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"

GameObject::GameObject()
{
	name = "Scene";
}

GameObject::GameObject(GameObject * parent)
{
	SetParent(parent);
}


GameObject::~GameObject()
{
}
void GameObject::CleanUp()
{
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		item->CleanUp();
	}

	for (int i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->CleanUp();
	}
	parent = nullptr;
}
void GameObject::Update()
{
	//Get Transform
	ComponentTransform* transform = NULL;
	transform = (ComponentTransform*)FindComponent(TRANSFORM);
	if (transform != nullptr)
	{
		glPushMatrix();
		glMultMatrixf((float*)&transform->GetInverseMatrix());
	}

	if (!enable)
		return;
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if(item->isEnable())
			item->Update();
	}
	for (int i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
			item->Update();

	}
	if (transform != nullptr)
	{
		//Pop Matrix
		glPopMatrix();
	}
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
		for (int i = 0; i < childs.size(); i++)
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
	 ImGui::Text(name.c_str());
//	 if (ImGui::InputText("##go_name", input_name, IM_ARRAYSIZE(input_name), ImGuiInputTextFlags_EnterReturnsTrue))
	// {
	//	 name = input_name;
	// }

	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		item->InspectorUpdate();
	}	
}

void GameObject::SetParent(GameObject * set_parent)
{
	if (set_parent == nullptr)
	{
		LOG("ERROR parent null");
		return;
	}
	parent = set_parent;
	set_parent->SetChild(this);
}

void GameObject::SetChild(GameObject * child)
{
	if (child == nullptr)
	{
		LOG("ERROR child null");
		return;
	}
	childs.push_back(child);
}

void GameObject::SetName(const char * set_name)
{
	name = set_name;
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
	case TRANSFORM:
		item = new ComponentTransform(this);
		break;
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
	for (int i = 0; i < components.size(); i++)
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
