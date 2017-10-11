#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "Primitive_p.h"
#include "ModuleCamera3D.h"

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
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

update_status ModuleScene::GuiUpdate()
{
	
	if (model != nullptr)
	{
		ImGui::Begin("Colision Menu");

		model->OnGuiDraw();
		ImGui::End();

	}

	return UPDATE_CONTINUE;
}



update_status ModuleScene::Update(float dt)
{
    //Draw modes
	if (model != nullptr)
	{
		model->Draw();

	}
	plane.Render();

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	return ret;
}
void ModuleScene::LoadModel(const char * path)
{
	LOG("Drag Model path:%s", path);
	if (model != nullptr)
	{

	}
	model=new Model(path);
	App->camera->Focus(model->GetCenter());

}

void ModuleScene::LoadTexture(const char * path)
{
	LOG("Drag Texture path:%s", path);
}

Model * ModuleScene::GetModel()
{
	return model;
}
