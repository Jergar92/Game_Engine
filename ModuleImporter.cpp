#include "Globals.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleImporter.h"
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

void ModuleImporter::Import(const char * path)
{
	dropped_filedir = path;
	std::size_t found = dropped_filedir.find_last_of('.');
	if (dropped_filedir.substr(found + 1) == "png" || dropped_filedir.substr(found + 1) == "jpg" || dropped_filedir.substr(found + 1) == "dds")
	{
		App->file_system->CloneFile(dropped_filedir.c_str());
		material.ImportTexture(dropped_filedir.c_str());
	}
	else
	{
		App->file_system->CloneFile(dropped_filedir.c_str());
		mesh.ImportMesh(dropped_filedir.c_str());
		//mesh.LoadMesh(dropped_filedir.c_str());

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

void ModuleImporter::LoadMesh(const char * name, ComponentMesh * component)
{
	char* buffer=nullptr;
	App->file_system->LoadFile(name, &buffer, App->file_system->GetMeshesFolder(), "frog");
	if (buffer != nullptr) {
		mesh.LoadMesh(buffer, component);
		RELEASE_ARRAY(buffer);
	}

}
int ModuleImporter::LoadTexture(const char * name, ComponentMeshRenderer * component)
{
	char* buffer = nullptr;
	App->file_system->LoadFile(name, &buffer, App->file_system->GetMaterialFolder(), "dds");

	std::string full_path(App->file_system->SetExtension(name, "dds"));
	full_path = App->file_system->SetPathFile(full_path.c_str(), App->file_system->GetMaterialFolder());
	return material.LoadTexture(full_path.c_str());

}