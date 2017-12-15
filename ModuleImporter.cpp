#include "Globals.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleImporter.h"
#include "ModuleScene.h"
#include "ComponentMeshRenderer.h"
#include "ComponentMesh.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
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

void ModuleImporter::Import(const char * path)
{
	dropped_filedir = path;
	std::size_t found = dropped_filedir.find_last_of('.');
	std::string extension = dropped_filedir.substr(found + 1);
	if (_stricmp(extension.c_str(), "png")==0
		|| _stricmp(extension.c_str(), "jpg") == 0
		|| _stricmp(extension.c_str(), "dds") == 0
		|| _stricmp(extension.c_str(), "tga") == 0)
	{
		App->file_system->CloneFile(dropped_filedir.c_str(), App->file_system->GetAssetsTextFolder());
		//material.ImportTexture(dropped_filedir.c_str());
	}
	else if(_stricmp(extension.c_str(), "obj") == 0 
		|| _stricmp(extension.c_str(), "fbx") == 0)
	{
		App->file_system->CloneFile(dropped_filedir.c_str(), App->file_system->GetAssetsMeshFolder());
	//	mesh.ImportMesh(dropped_filedir.c_str());
		//mesh.LoadMesh(dropped_filedir.c_str());

	}
	else if (_stricmp(extension.c_str(), "ttf") == 0)
	{
		App->file_system->CloneFile(dropped_filedir.c_str(), App->file_system->GetAssetsFolder());
	}
	else
	{
		App->file_system->CloneFile(dropped_filedir.c_str(), App->file_system->GetAssetsFolder());
	}

}



bool ModuleImporter::ImportTexture(const char * path, const char * name)
{
	return material.ImportTexture(path, name)==1;
}
bool ModuleImporter::ImportMesh(const char * path,const char* name)
{
	return mesh.ImportMesh(path, name);
}

bool ModuleImporter::ImportFont(const char * path, const char * name)
{
	return font.ImportFont(path,name);
}

void ModuleImporter::LoadMesh(ResourceMesh* r_mesh)
{
		mesh.LoadMesh(r_mesh);
}
int ModuleImporter::LoadTexture(ResourceTexture * r_text)
{

	return material.LoadTexture(r_text);

}

void ModuleImporter::LoadFont(ResourceFont * component)
{
	font.LoadFont(component);
	
}
