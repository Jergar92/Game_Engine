#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"

ModuleScene::ModuleScene(Application * app, bool start_enabled):Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;


	return ret;
}

update_status ModuleScene::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;


	return ret;
}
