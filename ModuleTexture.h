#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleTexture:public Module
{
public:
	ModuleTexture(bool start_enabled = true);
	~ModuleTexture();
	bool Start();
	bool CleanUp();

private:

};
