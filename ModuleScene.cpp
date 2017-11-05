#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ModuleImporter.h"
#include "ModuleEditorWindows.h"
#include "ModuleFileSystem.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "imgui\imgui.h"
#include "Primitive.h"
#include "p2Defs.h"
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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	scene_go = new GameObject();
	//Create Component Camera
	GameObject* camera = new GameObject(scene_go);
	camera->SetName("Camera Main");
	ComponentCamera* component_camera = (ComponentCamera*)camera->CreateComponent(ComponentType::CAMERA);
	
	App->editor_window->SetSceneGameObject(scene_go);
	
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
		scene_go->Update();

	}
	plane->Render();

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;
	delete plane;

	CleanGO();
	
	return ret;
}
void ModuleScene::CleanGO()
{
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
	char* buffer;
	uint size=config.Serialize(&buffer);
	config.Save("scene.json", path);
	config.CleanUp();
}

void ModuleScene::LoadScene()
{

	JSONConfig config;
	config.ParseFile("scene.json",App->file_system->GetAssetsFolder());

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
/*
void ModuleScene::SendToQuad(GameObject * go)
{
	quadtree.Insert(Data<GameObject*>(QuadPoint(go->position.x, go->position.z), go));
}
*/
