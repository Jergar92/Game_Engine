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
	else
	{
		App->file_system->CloneFile(dropped_filedir.c_str(), App->file_system->GetAssetsFolder());
	}

}

void ModuleImporter::Load(const char * path)
{
	dropped_filedir = path;
	std::size_t found = dropped_filedir.find_last_of('.');
	if (dropped_filedir.substr(found + 1) == "json")
	{
		
	}
	else if (dropped_filedir.substr(found + 1) == "png" || dropped_filedir.substr(found + 1) == "jpg" || dropped_filedir.substr(found + 1) == "dds")
	{

	}
	else
	{

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
void ModuleImporter::LoadMesh(const char * name, ComponentMesh * component)
{
	char* buffer=nullptr;
	App->file_system->LoadFile(name, &buffer, App->file_system->GetMeshesFolder(), "frog");
	if (buffer != nullptr) {
		mesh.LoadMesh(buffer, component);
		RELEASE_ARRAY(buffer);
	}

}
void ModuleImporter::LoadMesh(ResourceMesh* r_mesh)
{
	
		mesh.LoadMesh(r_mesh);
	

}
int ModuleImporter::LoadTexture(ResourceTexture * r_text)
{

	return material.LoadTexture(r_text);

}