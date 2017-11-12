#include "ModuleResourceManager.h"
#include "Application.h"
#include "ModuleEditorWindows.h"
#include "UI_Folder.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include <vector>
#include <experimental\filesystem>

#define UPDATE_RESOURCE_TIME 5.0f
ModuleResourceManager::ModuleResourceManager()
{
	name = "Resource Manager";
}


ModuleResourceManager::~ModuleResourceManager()
{
}

bool ModuleResourceManager::Start()
{
	std::vector<std::string> files = App->editor_window->ReturnFiles(F_META);
	for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		LoadMetaResource((*it).c_str());
	}
	return true;
}

update_status ModuleResourceManager::Update(float dt)
{

	time_update += dt;
	if (time_update > UPDATE_RESOURCE_TIME)
	{
		LookForResources();
	}
	return UPDATE_CONTINUE;
}

void ModuleResourceManager::LookForResources()
{

	time_update = 0.0f;
	std::vector<std::string> files = App->editor_window->ReturnFiles();
	for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		if (Find(it->c_str()) == 0)
		{
			ImportFile(it->c_str());
		}
	}
}

uint ModuleResourceManager::Find(const char * asset_file) const
{
	std::map<uint, Resource*>::const_iterator it = resources.begin();
	for (; it != resources.end(); it++)
	{
		if (std::experimental::filesystem::equivalent(it->second->GetOriginalFile(), asset_file))
			return it->second->GetUID();
	}
	return 0;
}

uint ModuleResourceManager::ImportFile(const char * new_asset_file)
{
	std::string asset = new_asset_file;
	std::size_t found = asset.find_last_of('.');
	bool import_success = false;
	ResourceType type = GetResourceFromFile(new_asset_file);
	uint UID = App->GenerateRandom();
	std::string name = std::to_string(UID);
	switch (type)
	{
	case R_NONE:
		break;
	case R_TEXTURE:
		import_success=App->importer->ImportTexture(new_asset_file, name.c_str());
		
		break;
	case R_MESH:
		import_success = App->importer->ImportMesh(new_asset_file, name.c_str());


		break;
	default:
		break;
	}

	if (import_success)
	{
		Resource* ret = CreateResource(type, UID);
		ret->SetOriginalFile(new_asset_file);
		ret->SetMetaFile(new_asset_file);

		switch (type)
		{
		case R_NONE:
			break;
		case R_TEXTURE:
			ret->SetLibraryFile(name.c_str(),"dds");
			break;
		case R_MESH:
			ret->SetLibraryFile(name.c_str(), "json");
			break;
		default:
			break;
		}


		JSONConfig config;
		ret->SaveResource(config);
		char* buffer = nullptr;
		uint size = config.Serialize(&buffer);
		config.Save(ret->GetMetaJsonFile().c_str());
		config.CleanUp();
		return ret->GetUID();

	}
	return 0;
}

const std::string ModuleResourceManager::GetLibraryPathFromOriginalPath(const char * original_path)
{
	std::map<uint, Resource*>::const_iterator it = resources.begin();
	for (; it != resources.end(); it++)
	{
		if (std::experimental::filesystem::equivalent(it->second->GetOriginalFile(), original_path))
			return it->second->GetLibraryFile();
	}
	return std::string();
}

ResourceType ModuleResourceManager::GetResourceFromFile(const char * file)
{
	std::string extension_check = file;
	std::size_t found = extension_check.find_last_of('.');
	std::string extension = extension_check.substr(found + 1);
	if (_stricmp(extension.c_str(), "png") == 0
		|| _stricmp(extension.c_str(), "jpg") == 0
		|| _stricmp(extension.c_str(), "dds") == 0
		|| _stricmp(extension.c_str(), "tga") == 0)
	{
		return R_TEXTURE;
	}
	else if (_stricmp(extension.c_str(), "obj") == 0
		|| _stricmp(extension.c_str(), "fbx") == 0)
	{
		return R_MESH;

	}
	else
	{
		return R_NONE;
	}
}
const Resource * ModuleResourceManager::Get(uint UID) const
{
	std::map<uint, Resource*>::const_iterator it = resources.find(UID);
	if (it != resources.end())
		return it->second;
	return nullptr;
}

Resource * ModuleResourceManager::Get(uint UID)
{
	std::map<uint, Resource*>::iterator it = resources.find(UID);
	if (it != resources.end())
		return it->second;
	return nullptr;
}

Resource * ModuleResourceManager::CreateResource(ResourceType type, uint custom_UID)
{
	Resource* ret = nullptr;
	uint UID = (custom_UID == -1) ? App->GenerateRandom() : custom_UID;
	switch (type)
	{
	case R_NONE:
		break;
	case R_TEXTURE:
		ret = new ResourceTexture(UID);
		break;
	case R_MESH:
		ret = new ResourceMesh(UID);
		break;
	default:
		break;
	}
	if (ret != nullptr)
	{
		resources[UID] = ret;
	}
	return ret;
}

void ModuleResourceManager::SaveMetaResource(const char* path)
{

}

void ModuleResourceManager::LoadMetaResource(const char* path)
{
		JSONConfig config;
		if (!config.ParseFile(path))
			return;
		Resource*resource = nullptr;
		resource = CreateResource(static_cast<ResourceType>(config.GetInt("Resource Type")), config.GetInt("Resource UID"));
		resource->LoadResource(config);
		config.CleanUp();
}
