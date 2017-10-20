#include "Application.h"
#include "Globals.h"
#include "ModuleFileSystem.h"
#include "p2Defs.h"
#include <iostream>
#include <fstream>
#define ASSETS_FOLDER "Assets"
#define LIBRARY_FOLDER "Library"
#define MESHES_FOLDER "Library/Meshes"
#define MATERIAL_FOLDER "Library/Material"
#define MESH_EXTENSION ".frog"

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
	meshes = MESHES_FOLDER;
	assets = ASSETS_FOLDER;
	materials = MATERIAL_FOLDER;

	CreateFolder(assets.c_str());
	CreateFolder(LIBRARY_FOLDER);
	CreateFolder(meshes.c_str(), true);
	CreateFolder(materials.c_str(),true);
	
	//Assets 
	//Library / Meshes
	//Library / Materials
	return ret;
}

bool ModuleFileSystem::CreateOwnFile(const char* name, char* buffer,int buffer_size, const char* directory)
{
	bool ret = true;
	std::string complete_path= directory;
	complete_path += "/";
	complete_path += name;
	complete_path += MESH_EXTENSION;


	std::fstream file_stream(complete_path.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);


	file_stream.write(buffer, buffer_size);

	return ret;
}

const char * ModuleFileSystem::GetMeshesFolder()
{
	return meshes.c_str();
}

const char * ModuleFileSystem::GetMaterialFolder()
{
	return materials.c_str();
}

const char * ModuleFileSystem::GetAssetsFolder()
{
	return assets.c_str();
}

void ModuleFileSystem::CreateFolder(const char * name, bool hide)
{

	if (CreateDirectory(name, NULL))
	{
		if (hide)
		{
			SetFileAttributes(name, FILE_ATTRIBUTE_HIDDEN);
		}
	}
	else
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{

			LOG("Directory (%s) already exists", name);
		}
	}
}

