#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleTexture:public Module
{
public:
	ModuleTexture(bool start_enabled = true);
	~ModuleTexture();
	bool Awake(const JSON_Object* data);
	int LoadTextureFromFile(const char* filename);
	bool Start();
	bool CleanUp();

private:

};
