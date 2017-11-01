#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "ModuleCamera3D.h"
#include "ModuleImporter.h"
#include "ModuleMenuBar.h"
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
	camera->AddComponent(component_camera);
	
	App->menu_bar->SetSceneGameObject(scene_go);

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
	if (scene_go != nullptr)
	{
		scene_go->CleanUp();
		RELEASE(scene_go);
	}
	
	return ret;
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

void ModuleScene::SaveScene()
{
	JSONConfig config;
	
	config.OpenArray("GameObject");
	scene_go->SaveGameObject(config);
	char* buffer;
	uint size=config.Serialize(&buffer);
	App->file_system->CreateOwnFile("scene", buffer, size, App->file_system->GetAssetsFolder(), "json");
	config.CleanUp();
}

void ModuleScene::LoadScene()
{
	JSONConfig config;
	config.SetFocus(App->file_system->GetPathFile("scene.json", App->file_system->GetAssetsFolder()));
	uint size = config.GetArraySize("Game Objects");
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = config.SetFocusArray("Game Objects", i);
		GameObject* item = new GameObject();
		

		item->LoadGameObject(config_item);

		if (i == 0)
			scene_go = item;
	}

}
/*
void ModuleScene::SendToQuad(GameObject * go)
{
	quadtree.Insert(Data<GameObject*>(QuadPoint(go->position.x, go->position.z), go));
}
*/
