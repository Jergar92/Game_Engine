#include "ModuleResourceManager.h"



ModuleResourceManager::ModuleResourceManager()
{
}


ModuleResourceManager::~ModuleResourceManager()
{
}

uint ModuleResourceManager::Find(const char * asset_file) const
{
	return uint();
}

uint ModuleResourceManager::ImportFile(const char * new_asset_file)
{
	return uint();
}

const Resource * ModuleResourceManager::Get(uint UID) const
{
	return nullptr;
}

Resource * ModuleResourceManager::Get(uint UID)
{
	return nullptr;
}

Resource * ModuleResourceManager::CreateResource(ResourceType type)
{
	switch (type)
	{
	case R_NONE:
		break;
	case R_TEXTURE:
		break;
	case R_MESH:
		break;
	default:
		break;
	}
	return nullptr;
}
