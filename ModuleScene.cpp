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
	return ret;
}

update_status ModuleScene::GuiUpdate()
{
	

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
bool ModuleScene::CleanUp()
{
	bool ret = true;
	delete plane;
	if (scene_go != nullptr)
	{
		CleanGO();
	}
	return ret;
}
void ModuleScene::CleanGO()
{
//	App->editor_window->SetSelectedGameObject(nullptr);

	if (scene_go != nullptr)
	{
		scene_go->CleanUp();
		RELEASE(scene_go);
	}
}
GameObject * ModuleScene::GenerateGameObject(GameObject * parent)
{
	GameObject* new_go = new GameObject(parent);

	return new_go;
}



GameObject* ModuleScene::GetScene()const 
{
	return scene_go;
}

void ModuleScene::LoadTexture(const char * path)
{
	LOG("Drag Texture path:%s", path);


	if (scene_go != nullptr)
	{
		LOG("ERROR no model to overlay texture");

		//model->OverlayTexture(path);
	}
	else
	{
		LOG("ERROR no model to overlay texture");
	}
}

void ModuleScene::SendGameObject(GameObject * go)
{
	go->SetParent(scene_go);
}

void ModuleScene::SaveScene(const char*path)const 
{
	JSONConfig config;
	
	config.OpenArray("GameObject");
	scene_go->SaveGameObject(config);
	char* buffer=nullptr;
	uint size=config.Serialize(&buffer);
	config.Save(path);
	config.CleanUp();
}

void ModuleScene::LoadScene(const char*path)
{
	CleanGO();

	JSONConfig config;

	if (!config.ParseFile(path))
		return;

	uint size = config.GetArraySize("GameObject");
	std::vector < GameObject*> tmp_go;
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = config.SetFocusArray("GameObject", i);
		GameObject* item = new GameObject();
		

		item->LoadGameObject(config_item);
		tmp_go.push_back(item);

	}
	for (int i = 0; i < tmp_go.size(); i++)
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
	for (int i = 0; i < go.size(); i++)
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
			if (add_elements.front()->IsStatic())
			{
				quadtree->Insert(add_elements.front());
			}
			GameObject* first_position = add_elements.front();
			for (int i = 0; i < first_position->childs.size(); i++)
			{
				add_elements.push(first_position->childs[i]);
			}
			add_elements.pop();
		}
		
	}
	
}


void ModuleScene::LoadGO(const char*path)
{
	std::string library_path = App->resource_manager->GetLibraryPathFromOriginalPath(path);
	JSONConfig config;

	if (!config.ParseFile(library_path.c_str(),App->file_system->GetMeshesFolder()))
		return;

	uint size = config.GetArraySize("GameObject");
	std::vector < GameObject*> tmp_go;
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = config.SetFocusArray("GameObject", i);
		GameObject* item = new GameObject();


		item->LoadGameObject(config_item);
		tmp_go.push_back(item);

	}
	for (int i = 0; i < tmp_go.size(); i++)
	{

		GameObject* item = tmp_go[i];
		if (item->GetParentUID() == 0)
		{
			item->SetParent(scene_go);
		}
		else
		{
			item->SetParent(FindGameObjectByID(tmp_go, item->GetParentUID()));
			item->GenerateBoudingBox();
		}
		item->UpdateMatrix();

	}
	config.CleanUp();
	App->editor_window->SetSceneGameObject(scene_go);

}
/*
void ModuleScene::SendToQuad(GameObject * go)
{
	quadtree.Insert(Data<GameObject*>(QuadPoint(go->position.x, go->position.z), go));
}
*/
