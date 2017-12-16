#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "ModuleCamera.h"
#include "ModuleImporter.h"
#include "ModuleEditorWindows.h"
#include "ModuleResourceManager.h"
#include "MyQuadTree.h"
#include "ModuleFileSystem.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "imgui\imgui.h"
#include "Primitive.h"
#include "p2Defs.h"
#include <conio.h>
#include <queue>
#include "EventSystem.h"
ModuleScene::ModuleScene(bool start_enabled)
{
	name = "Scene";
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;
	plane = new Plane_p;

	//App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(float3(0, 0, 0));
	
	scene_go = new GameObject();
	scene_go->SetName("Scene");
	//Create Component Camera
	GameObject* camera = new GameObject(scene_go);
	camera->SetName("Camera Main");
	ComponentCamera* component_camera = (ComponentCamera*)camera->CreateComponent(ComponentType::CAMERA);
	quadtree = new MyQuadTree();
	App->editor_window->SetSceneGameObject(scene_go);
	
	GenerateQuadTree();


	EventVoid play;
	play.Create<ModuleScene>("OnPlay", this, &ModuleScene::OnPlay);
	EventS->AddEvent(play);

	EventVoid stop;
	play.Create<ModuleScene>("OnStop", this, &ModuleScene::OnStop);
	EventS->AddEvent(stop);
	return ret;
}

update_status ModuleScene::GuiUpdate()
{
	

	return UPDATE_CONTINUE;
}


update_status ModuleScene::PreUpdate(float dt)
{
	if (scene_go != nullptr)
	{
		scene_go->PreUpdate(dt);

	}
	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update(float dt)
{
    //Draw modes
	if (scene_go != nullptr)
	{
		scene_go->Update(dt);

	}
	if (enable_draw_quadtree)
	{
		quadtree->DrawQuadtree();
	}
	plane->Render();

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	if (scene_go != nullptr)
	{
		scene_go->PostUpdate(dt);

	}
	return UPDATE_CONTINUE;
}
void ModuleScene::OnPlay()
{
	if (scene_go != nullptr)
	{
		scene_go->OnPlay();

	}
}
void ModuleScene::OnStop()
{
	if (scene_go != nullptr)
	{
		scene_go->OnStop();

	}
}
bool ModuleScene::CleanUp()
{
	bool ret = true;
	delete plane;
	quadtree->CleanUp();

	delete quadtree;
	if (scene_go != nullptr)
	{
		scene_go->CleanUp();
		RELEASE(scene_go);
	}
	return ret;
}
void ModuleScene::CleanGO()
{

	if (scene_go != nullptr)
	{
		scene_go->Delete();
		RELEASE(scene_go);
	}
}
GameObject * ModuleScene::GenerateGameObject(GameObject * parent)
{
	GameObject* new_go = new GameObject(parent);
	
	no_static_list.push_back(new_go);

	return new_go;
}

void ModuleScene::GoStaticEnable(bool is_static, GameObject* static_go)
{
	if(is_static == true)
	{
		//no_static_list.remove(static_go);
		quadtree->Insert(static_go);
		static_go->SetStatic(is_static);
	}

}


GameObject* ModuleScene::GetScene()const 
{
	return scene_go;
}


void ModuleScene::SendGameObject(GameObject * go)
{
	go->SetParent(scene_go);
}
void ModuleScene::EventTry()
{
	LOG("Event Active");
}
void ModuleScene::SaveScene(const char*path)const 
{
	JSONConfig config;
	
	config.OpenArray("GameObject");
	scene_go->SaveGameObject(config);
	char* buffer=nullptr;
	uint size=config.Serialize(&buffer);
	config.Save(path);
	if (buffer != nullptr)
	RELEASE_ARRAY(buffer);
}

void ModuleScene::LoadScene(const char*path)
{
	CleanGO();
	quadtree->CleanUp();
	JSONConfig config;

	if (!config.ParseFile(path))
		return;

	uint size = config.GetArraySize("GameObject");
	std::vector < GameObject*> tmp_go;
	for (uint i = 0; i < size; i++)
	{
		JSONConfig config_item = config.SetFocusArray("GameObject", i);
		GameObject* item = GenerateGameObject();
		

		item->LoadGameObject(config_item);
		tmp_go.push_back(item);

	}
	for (uint i = 0; i < tmp_go.size(); i++)
	{
		
		GameObject* item = tmp_go[i];
		if (item->GetParentUID() == 0)
		{
			scene_go = item;
		}
		else
		{
			item->SetParent(FindGameObjectByID(tmp_go, item->GetParentUID()));
		}
		item->UpdateMatrix();

	}
	config.CleanUp();
	App->editor_window->SetSceneGameObject(scene_go);

}
GameObject * ModuleScene::FindGameObjectByID(const std::vector<GameObject*>& go, int UID_to_find) const
{
	for (uint i = 0; i < go.size(); i++)
	{
		GameObject* item = go[i];
		if (item->GetUID() == UID_to_find)
		{
			return item;
		}
	}
	return nullptr;
}

void ModuleScene::GenerateQuadTree()
{
	if(quadtree != nullptr)
	quadtree->CleanUp();

	if (scene_go != nullptr)
	{
		std::queue<GameObject*> add_elements;
		quadtree->SetQuadtree(scene_go);
		add_elements.push(scene_go);
		
		while (!add_elements.empty())
		{
			if (add_elements.front()->GetStatic())
			{
				quadtree->Insert(add_elements.front());
			}
			GameObject* first_position = add_elements.front();
			for (uint i = 0; i < first_position->childs.size(); i++)
			{
				add_elements.push(first_position->childs[i]);
			}
			add_elements.pop();
		}
		
	}
	
}


void ModuleScene::LoadGO(const char*path)
{
	uint resource_UID=App->resource_manager->Find(path);
	if (resource_UID != 0)
	{
		Resource* resource = App->resource_manager->Get(resource_UID);

		if (resource->GetResourceType() == R_PREFAB)
		{
			resource->LoadInMemory();
		}
	}
}
/*
void ModuleScene::SendToQuad(GameObject * go)
{
	quadtree.Insert(Data<GameObject*>(QuadPoint(go->position.x, go->position.z), go));
}
*/
