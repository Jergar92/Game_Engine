#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleTexture.h"
#include "ModuleScene.h"
#include "ComponentMeshRenderer.h"
#include "ComponentMesh.h"
#include "GameObject.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
ModuleImporter::ModuleImporter()
{
	name = "Importer";
}


ModuleImporter::~ModuleImporter()
{
}

bool ModuleImporter::Start()
{
	bool ret = true;
	if (!material.Init())
		ret = false;
	return ret;
}

void ModuleImporter::Load(const char * path)
{
	dropped_filedir = path;
	std::size_t found = dropped_filedir.find_last_of('.');
	if (dropped_filedir.substr(found + 1) == "png" || dropped_filedir.substr(found + 1) == "jpg" || dropped_filedir.substr(found + 1) == "dds")
	{
	}
	else
	{
		mesh.ImportMesh(dropped_filedir.c_str());
		//mesh.LoadMesh(dropped_filedir.c_str());

	}
}
