#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "Primitive.h"


ModuleScene::ModuleScene(bool start_enabled)
{
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




update_status ModuleScene::Update(float dt)
{
	plane.Render();

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	return ret;
}
