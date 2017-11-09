#include "ModuleResourceManager.h"
#include "Application.h"
#include "ModuleEditorWindows.h"
#include "UI_Folder.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include <vector>
#define UPDATE_RESOURCE_TIME 5.0f
ModuleResourceManager::ModuleResourceManager()
{
	name = "Resource Manager";
}


ModuleResourceManager::~ModuleResourceManager()
{
}

update_status ModuleResourceManager::Update(float dt)
{

	time_update += dt;
	if (time_update > UPDATE_RESOURCE_TIME)
	{
		time_update = 0.0f;
		std::vector<std::string> files = App->editor_window->ReturnFiles("json");
		for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); it++)
		{
			if (Find(it->c_str()) == 0)
			{
				ImportFile(it->c_str());
			}
		}
		//get all folders 
		//find all folders on resource
		//if return 0 create that assets
		//load

	}
	return UPDATE_CONTINUE;
}

uint ModuleResourceManager::Find(const char * asset_file) const
{
	std::map<uint, Resource*>::const_iterator it = resources.begin();
	for (; it != resources.end(); it++)
	{
		if (it->second->GetOriginalFile().compare(asset_file) == 0)
			return it->second->GetUID();
	}
	return 0;
}

uint ModuleResourceManager::ImportFile(const char * new_asset_file)
{
	return uint();
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

Resource * ModuleResourceManager::CreateResource(ResourceType type)
{
	Resource* ret = nullptr;
	uint UID = App->GenerateRandom();
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
