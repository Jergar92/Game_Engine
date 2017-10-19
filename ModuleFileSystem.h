#pragma once
#include "Module.h"

class ModuleFileSystem:public Module
{
public:
	ModuleFileSystem();
	~ModuleFileSystem();
	bool Awake(const JSON_Object* data);
private:
	void CreateFolder(const char* name,  bool hide = false);
};

