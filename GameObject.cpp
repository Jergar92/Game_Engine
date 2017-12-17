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
#include "ComponentTransform.h"
#include "ComponentRectTransform.h"
#include "ResourceMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"
#include "ComponentCanvas.h"
#include "ComponentCanvasRenderer.h"
#include "ComponentImage.h"
#include "ComponentButton.h"
#include "ComponentText.h"
#include "ComponentInputText.h"
#include "ComponentCheckBox.h"
#include "ComponentPanel.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"
#include <queue>
#define MAX_NAME 20

GameObject::GameObject(GameObjectType type ,float3 scale, Quat rotation, float3 position) :name("Game Object"),type(type), parent(nullptr)
{
	UID = App->GenerateRandom();
	CreateTransform(scale, rotation, position);
	
	input_name = name;
	UpdateMatrix();

}

GameObject::GameObject(GameObject * parent, GameObjectType type , float3 scale, Quat rotation, float3 position) :name("Game Object"), type(type)
{
	UID = App->GenerateRandom();
	SetParent(parent);

	CreateTransform(scale, rotation, position);

	input_name = name;

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
	components.clear();

	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		

		item->CleanUp();
		RELEASE(item);

	}	
	name.clear();
	childs.clear();
	parent = nullptr;

}
void GameObject::PreUpdate(float dt)
{
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if (item->ToDelete())
		{
			if (RemoveComponent(item->type, i))
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
				item->to_delete = false;
				LOG("Remove GameObject Fail");
			}
		}
		else
			item->PreUpdate(dt);
	}
}
void GameObject::OnPlay()
{

	if (!enable)
		return;

	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if (item->isEnable())
			item->OnPlay();
	}
	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->OnPlay();
	}
}
void GameObject::OnStop()
{

	if (!enable)
		return;

	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if (item->isEnable())
			item->OnStop();
	}
	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];
		item->OnStop();
	}
}
void GameObject::Update(float dt)
{

	if (!enable)
		return;

	for (uint i = 0; i < components.size(); i++)
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

	if (enable_fade == true)
	{
		ActivateFade(50.0f * dt);
	}

}

void GameObject::PostUpdate(float dt)
{
	

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
	char name_id[80];
	sprintf_s(name_id, 80, "%s##%i", name.c_str(), UID);
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
				App->scene->GenerateGameObject(type,this);
				ImGui::CloseCurrentPopup();

			}
			if (ImGui::Button("Create Canvas"))
			{
				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type,this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
				}
				else
				{
					LOG("Canvas is already created");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Create Image"))
			{
				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);

				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type,this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
					GameObject* image = App->scene->GenerateGameObject(GO_CANVAS,main_go);
					image->SetName("Image");
					image->CreateComponent(ComponentType::CANVAS_IMAGE);
				}
				else
				{
					if (IsRelated(main_go))
					{
						GameObject* image = App->scene->GenerateGameObject(type,this);
						image->SetName("Image");
						image->CreateComponent(ComponentType::CANVAS_IMAGE);
					}
				}
			



				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Create Panel"))
			{

				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);

				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type, this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
					GameObject* panel = App->scene->GenerateGameObject(GO_CANVAS, main_go);
					panel->SetName("Panel");
					panel->CreateComponent(ComponentType::CANVAS_IMAGE);
					panel->CreateComponent(ComponentType::CANVAS_IMDRAG);

				}
				else
				{
					if (IsRelated(main_go))
					{
						GameObject* panel = App->scene->GenerateGameObject(type, this);
						panel->SetName("Panel");
						panel->CreateComponent(ComponentType::CANVAS_IMAGE);
						panel->CreateComponent(ComponentType::CANVAS_IMDRAG);

					}
				}
			}
			if (ImGui::Button("Create Button"))
			{

				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);

				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type, this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
					GameObject* button = App->scene->GenerateGameObject(GO_CANVAS, main_go);
					button->SetName("Button");
					button->CreateComponent(ComponentType::CANVAS_IMAGE);
					button->CreateComponent(ComponentType::CANVAS_BUTTON);

				}
				else
				{
					if (IsRelated(main_go))
					{
						GameObject* button = App->scene->GenerateGameObject(type, this);
						button->SetName("Button");
						button->CreateComponent(ComponentType::CANVAS_IMAGE);
						button->CreateComponent(ComponentType::CANVAS_BUTTON);

					}
				}
			}
			if (ImGui::Button("Create CheckBox"))
			{

				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);

				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type, this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
					GameObject* check_box = App->scene->GenerateGameObject(GO_CANVAS, main_go);
					check_box->SetName("Check Box");
					check_box->CreateComponent(ComponentType::CANVAS_IMAGE);
					check_box->CreateComponent(ComponentType::CANVAS_CHECKBOX);

				}
				else
				{
					if (IsRelated(main_go))
					{
						GameObject* check_box = App->scene->GenerateGameObject(type, this);
						check_box->SetName("Check Box");
						check_box->CreateComponent(ComponentType::CANVAS_IMAGE);
						check_box->CreateComponent(ComponentType::CANVAS_CHECKBOX);

					}
				}
			}
			if (ImGui::Button("Create Texto"))
			{

				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);

				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type, this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
					GameObject* text = App->scene->GenerateGameObject(GO_CANVAS, main_go);
					text->SetName("Text");
					text->CreateComponent(ComponentType::CANVAS_TEXT);
				}
				else
				{
					if (IsRelated(main_go))
					{
						GameObject* text = App->scene->GenerateGameObject(type, this);
						text->SetName("Text");
						text->CreateComponent(ComponentType::CANVAS_TEXT);
					}
				}
			}
			if (ImGui::Button("Create InputText"))
			{

				GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);

				if (main_go == nullptr)
				{
					main_go = App->scene->GenerateGameObject(type, this);
					main_go->SetName("Canvas");
					main_go->CreateComponent(ComponentType::CANVAS);
					GameObject* text = App->scene->GenerateGameObject(GO_CANVAS, main_go);
					text->SetName("Input Text");
					text->CreateComponent(ComponentType::CANVAS_TEXT);
					text->CreateComponent(ComponentType::CANVAS_INPUT_TEXT);
				}
				else
				{
					if (IsRelated(main_go))
					{
						GameObject* text = App->scene->GenerateGameObject(type, this);
						text->SetName("Input Text");
						text->CreateComponent(ComponentType::CANVAS_TEXT);
						text->CreateComponent(ComponentType::CANVAS_INPUT_TEXT);
					}
				}
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
	{
		gui_static = true;
		App->scene->GoStaticEnable(static_go,this);
	}
	if (gui_static)
		OpenStaticQuestion();

	ImGui::Checkbox("Bounding Box ##show_bb", &show_bounding_box);
	//Start draw Elements 
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
				std::queue<GameObject*> queue;
				queue.push(this);
				while (!queue.empty())
				{
					GameObject* item = queue.front();
					for (std::vector<GameObject*>::iterator it = item->childs.begin(); it != item->childs.end(); it++)
					{
						queue.push(*it);
					}
					App->scene->GoStaticEnable(static_go, item);
					queue.pop();
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

void GameObject::CreateTransform(float3 scale, Quat rotation, float3 position)
{
	if (type == GO_ELEMENT)
	{
		if (parent != nullptr)
		{
			if (parent->type == GO_CANVAS)
			{
				type = GO_CANVAS;
				my_ui_transform = (ComponentRectTransform*)CreateComponent(ComponentType::RECT_TRANSFORM);
				my_ui_transform->SetTransform(scale, rotation, position);
				return;
			}
		}
		my_transform = (ComponentTransform*)CreateComponent(ComponentType::TRANSFORM);
		my_transform->SetTransform(scale, rotation, position);
	}
	else if (type == GO_CANVAS)
	{
		my_ui_transform = (ComponentRectTransform*)CreateComponent(ComponentType::RECT_TRANSFORM);
		my_ui_transform->SetTransform(scale, rotation, position);
	}
}




void GameObject::SetStatic(bool set)
{
	static_go = set;
}

bool GameObject::GetStatic() const
{
	return static_go;
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

void GameObject::ChangeUID()
{
	UID = App->GenerateRandom();
	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		(*it)->parent_UID = UID;
	}
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


	uint size = data.GetArraySize("Components");
	for (uint i = 0; i < size; i++)
	{
		JSONConfig config_item = data.SetFocusArray("Components", i);
		if (config_item.GetInt("Type") == -1)
		{
			my_transform->LoadComponent(config_item);
		}
		else if (config_item.GetInt("Type") == -2)
		{
			my_ui_transform->LoadComponent(config_item);
		}
		else
		{
			Component*item = CreateComponent((ComponentType)config_item.GetInt("Type"));
			item->LoadComponent(config_item);
		}
	
	}
	//Create and Set all components
}

void GameObject::SaveGameObject(JSONConfig& data)const
{
	JSONConfig config;
	config.SetInt(UID, "UID");
	config.SetInt(parent_UID, "ParentUID");
	config.SetInt(type, "TransformType");

	config.SetString(name, "Name");

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

void GameObject::ActivateFade(float speed)
{
	   if(my_ui_transform->position.y + my_ui_transform->GetHeight() > 0.0f)
	   {
			   my_ui_transform->position.y -= speed;
			   my_ui_transform->UpdateMatrix();
	   }

	   if(my_ui_transform->position.y + my_ui_transform->GetHeight() <= 0.0f)
	   {
		   enable_fade = false;
		   enable = false;
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
	case TRANSFORM:

		item = new ComponentTransform(this);

		break;
	case RECT_TRANSFORM:
		
		item = new ComponentRectTransform(this);
		if (this->type == GO_ELEMENT)
		{
			my_transform->DeleteComponent();
			RELEASE(components[0]);
			components.at(0) = item;
			this->type = GO_CANVAS;
			my_transform = nullptr;
			my_ui_transform = (ComponentRectTransform*)item;
			return item;

		}

		break;
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
	case CANVAS:
		if (this->type == GO_ELEMENT)
		{
			CreateComponent(RECT_TRANSFORM);
		}
		item = new ComponentCanvas(this);
		break;
	case CANVAS_RENDER:
		
		item = new ComponentCanvasRenderer(this);
		break;
	case CANVAS_IMAGE:
	{
		if (HaveComponent(CANVAS_TEXT))
		{
			LOG("Can Create component, component Text create conflict");
			break;
		}
		if (this->type == GO_ELEMENT)
		{
			CreateComponent(RECT_TRANSFORM);
		}
		Component* canvas_render = FindComponent(ComponentType::CANVAS_RENDER);;

		if (canvas_render==nullptr)
		{
			LOG("Add Component Canvas Render")
				canvas_render = CreateComponent(CANVAS_RENDER);
		}
		item = new ComponentImage(this);
		if(canvas_render!=nullptr)
		((ComponentCanvasRenderer*)canvas_render)->GetComponent(item);
		break;
	}
	case CANVAS_TEXT:
	{
		if (HaveComponent(CANVAS_IMAGE))
		{
			LOG("Can Create component, component Image create conflict");
			break;
		}
		if (this->type == GO_ELEMENT)
		{
			CreateComponent(RECT_TRANSFORM);
		}
		Component* canvas_render = FindComponent(ComponentType::CANVAS_RENDER);;

		if (canvas_render == nullptr)
		{
			LOG("Add Component Canvas Render")
				canvas_render = CreateComponent(CANVAS_RENDER);
		}
		item = new ComponentText(this);
		if (canvas_render != nullptr)
		((ComponentCanvasRenderer*)canvas_render)->GetComponent(item);
		break;
	}

	case CANVAS_INPUT_TEXT:
	{
		if (HaveComponent(CANVAS_IMAGE))
		{
			LOG("Can Create component, component Image create conflict");
			break;
		}
		if (this->type == GO_ELEMENT)
		{
			CreateComponent(RECT_TRANSFORM);
		}
		if (!HaveComponent(CANVAS_TEXT))
		{
			LOG("Add Component Canvas Text")
			CreateComponent(CANVAS_TEXT);

		}
		item = new ComponentInputText(this);
		break;
	}
	case CANVAS_BUTTON:
		if (HaveComponent(CANVAS_TEXT))
		{
			LOG("Can Create component, component Text create conflict");
			break;
		}
		if (this->type == GO_ELEMENT)
		{
			CreateComponent(RECT_TRANSFORM);

		
		}
		if (!HaveComponent(CANVAS_IMAGE))
		{
			LOG("Add Component Canvas Text")
				CreateComponent(CANVAS_IMAGE);

		}
		item = new ComponentButton(this);
		break;
	case CANVAS_CHECKBOX:
		if (HaveComponent(CANVAS_TEXT))
		{
			LOG("Can Create component, component Text create conflict");
			break;
		}
		if (this->type == GO_ELEMENT)
		{
			CreateComponent(CANVAS_CHECKBOX);
		
		}
		if (!HaveComponent(CANVAS_IMAGE))
		{
			LOG("Add Component Canvas Text")
				CreateComponent(CANVAS_IMAGE);

		}
		item = new ComponentCheckBox(this);
		break;
	case CANVAS_IMDRAG:
		if (HaveComponent(CANVAS_TEXT))
		{
			LOG("Can Create component, component Text create conflict");
			break;
		}

		if (this->type == GO_ELEMENT)
		{
			CreateComponent(RECT_TRANSFORM);
		}

		if (this->type == GO_ELEMENT)
		{
			CreateComponent(CANVAS_IMDRAG);

		}
		if (!HaveComponent(CANVAS_IMAGE))
		{
			LOG("Add Component Canvas Text")
				CreateComponent(CANVAS_IMAGE);

		}
		item = new ComponentPanel(this);
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

bool GameObject::FindGameObjectWithComponent(ComponentType type)const
{
	Component* ret = nullptr;
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];

		if (item->type == type)
		{
			return true;
		}
	}
	return false;
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
	else if (type == CANVAS_RENDER)
	{
		if (HaveComponent(CANVAS_IMAGE))
		{
			LOG("You cant remove a component canvas render if you have a component canvas image");
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
	
	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];

		if (item == to_remove)
		{

			childs.erase(childs.begin() + i);
			item->Delete();
			App->scene->no_static_list.remove(item);
			App->scene->quadtree->RemoveGameObject(item);
			RELEASE(item);
			return true;
		}
	}
	return false;
}
bool GameObject::HaveComponent(ComponentType type) const
{
	Component* ret = nullptr;
	for (uint i = 0; i < components.size(); i++)
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

void GameObject::Delete()
{
	
	if (App->editor_window->GetSelectedGameObject() == this)
		App->editor_window->SetSelectedGameObject(nullptr);
	
	for (uint i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		item->CleanUp();
		RELEASE(item);

	}

	for (uint i = 0; i < childs.size(); i++)
	{
		GameObject* item = childs[i];


		item->Delete();
		App->scene->no_static_list.remove(item);
		App->scene->quadtree->RemoveGameObject(item);
		RELEASE(item);

	}
	parent = nullptr;
}

const ComponentRectTransform* GameObject::GetRectTransform()const
{
	return my_ui_transform;
}

ComponentRectTransform * GameObject::GetRectTransform()
{
	return my_ui_transform;
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

	my_transform->SetTransform(set_scale, set_rotation, set_position);

}

void GameObject::UpdateMatrix()
{
	if (type == GO_ELEMENT)
	{
		my_transform->UpdateMatrix();
	}
	else if (type == GO_CANVAS)
	{
		my_ui_transform->UpdateMatrix();
	}
}

void GameObject::UpdateBoundingBox()
{

	global_bounding_box_OBB = indentity_bounding_box_AABB.Transform(my_transform->GetGlobalMatrix());

	global_bounding_box_AABB = indentity_bounding_box_AABB;
	global_bounding_box_AABB.TransformAsAABB(my_transform->GetGlobalMatrix());
	is_bounding_box_transformed = true;
	
}

float4x4 GameObject::GetTransposedMatrix()const
{
	if (type == GO_ELEMENT)
	{
		return my_transform->GetTransposedMatrix();
	}
	else if (type == GO_CANVAS)
	{
		return my_ui_transform->GetTransposedMatrix();
	}
	
}

float4x4 GameObject::GetGlobalMatrix() const
{
	if (type == GO_ELEMENT)
	{
		return my_transform->GetGlobalMatrix();
	}
	else if (type == GO_CANVAS)
	{
		return my_ui_transform->GetGlobalMatrix();
	}
	
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

AABB GameObject::GetIdentityBoundingBoxAABB() const
{
	return indentity_bounding_box_AABB;
}

GameObjectType GameObject::GetType() const
{
	return type;
}


void GameObject::GenerateBoudingBox()
{
	ComponentMesh* mesh = (ComponentMesh*)FindComponent(MESH);
	indentity_bounding_box_AABB.SetNegativeInfinity();
	if (mesh != nullptr)
	{
		if (mesh->HaveResourceMesh())
		{
			for (int i = 0; i < mesh->GetVertices().size(); i++)
			{
				indentity_bounding_box_AABB.Enclose(mesh->GetVertices()[i].position);
			}
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

void GameObject::SetEnableFade(bool value)
{
	enable_fade = value;
}

void GameObject::RenderBoundingBoxAABB()
{
	glBegin(GL_LINES);
	
		for (uint i = 0; i < 12; i++)
		{
			glVertex3f(global_bounding_box_AABB.Edge(i).a.x, global_bounding_box_AABB.Edge(i).a.y, global_bounding_box_AABB.Edge(i).a.z);
			glVertex3f(global_bounding_box_AABB.Edge(i).b.x, global_bounding_box_AABB.Edge(i).b.y, global_bounding_box_AABB.Edge(i).b.z);
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

bool GameObject::IsRelated(GameObject * parent) const
{
	std::queue<GameObject*> queue;
	queue.push(parent);
	while (!queue.empty())
	{
		GameObject* item = queue.front();
		for (std::vector<GameObject*>::iterator it = item->childs.begin(); it != item->childs.end(); it++)
		{
			queue.push(*it);
		}
		if (queue.front() == this)
		{
			return true;
		}
		queue.pop();
	}
	return false;
}

