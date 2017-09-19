#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleConsole : public Module
{
public:
	ModuleConsole(Application* app, bool start_enabled = true);
	~ModuleConsole();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();



public:
	
	static void ShowExampleAppConsole(bool* open);

private:
	
	bool show_app_console = false;

};