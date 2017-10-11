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
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_Once);
	if (model != nullptr)
	{
		ImGui::Begin("Colision Menu",(bool*)1, window_flags);

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
	if (model != nullptr)
	{
		model->CleanUp();
	}
	return ret;
}
void ModuleScene::LoadModel(const char * path)
{
	LOG("Drag Model path:%s", path);
	if (model != nullptr)
	{
		model->CleanUp();
		RELEASE(model);
	}
	model=new Model(path);
	App->camera->Focus(model->GetCenter());

}

void ModuleScene::LoadTexture(const char * path)
{
	LOG("Drag Texture path:%s", path);


	if (model != nullptr)
	{
		model->OverlayTexture(path);
	}
	else
	{
		LOG("ERROR no model to overlay texture");
	}
}

Model * ModuleScene::GetModel()
{
	return model;
}
