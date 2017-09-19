#include "Application.h"
#include "Globals.h"
#include"ModuleConsole.h"

ModuleConsole::ModuleConsole(Application * app, bool start_enabled) :Module(app, start_enabled)
{
}


ModuleConsole::~ModuleConsole()
{
}

bool ModuleConsole::Start()
{
	bool ret = true;


	return ret;
}

update_status ModuleConsole::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleConsole::CleanUp()
{
	bool ret = true;


	return ret;
}

