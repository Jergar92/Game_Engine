#include "Application.h"
#include "Globals.h"
#include "ModuleFileSystem.h"
#include <iostream>
#include <fstream>
#define ASSETS_FOLDER "Assets"
#define LIBRARY_FOLDER "Library"
#define MESHES_FOLDER "Library/Meshes"
#define MATERIAL_FOLDER "Library/Material"


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
	CreateFolder(ASSETS_FOLDER);
	CreateFolder(LIBRARY_FOLDER);
	CreateFolder(MESHES_FOLDER, true);
	CreateFolder(MATERIAL_FOLDER,true);
	
	//Assets 
	//Library / Meshes
	//Library / Materials
	return ret;
}



void ModuleFileSystem::CreateFolder(const char * name, bool hide)
{

	if(CreateDirectory(name, NULL))
	if (hide)
	{
		SetFileAttributes(name, FILE_ATTRIBUTE_HIDDEN);
	}
	else
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{

			LOG("Directory (%s) already exists", name);
		}
	}
}

