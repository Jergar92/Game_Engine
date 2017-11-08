#include "ModuleResourceManager.h"
#include "Application.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
ModuleResourceManager::ModuleResourceManager()
{
	name = "Resource Manager";
}


ModuleResourceManager::~ModuleResourceManager()
{
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
