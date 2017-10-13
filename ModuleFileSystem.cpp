#include "Application.h"
#include "Globals.h"
#include "ModuleFileSystem.h"
#include <direct.h>



ModuleFileSystem::ModuleFileSystem()
{
	name = "File System";
}


ModuleFileSystem::~ModuleFileSystem()
{
}

bool ModuleFileSystem::Awake(const JSON_Object * data)
{
	bool ret = true;
	CreateFolder("Assets");
	CreateFolder("Library");
	CreateFolder("Library/Meshes");
	CreateFolder("Library/Materials");


	
	//Assets 
	//Library / Meshes
	//Library / Materials
	return ret;
}

void ModuleFileSystem::CreateFolder(const char * name)
{
	if (mkdir(name) == -1)
	{
		if (errno == EEXIST) {
			LOG("try already exist")
				// alredy exists
		}
		else {
			// something else
			LOG("error exist")
		}
	}
}
