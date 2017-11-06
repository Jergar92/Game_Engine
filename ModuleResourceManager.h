#pragma once
#include "Globals.h"
#include "Resource.h"
class Resource;
class ModuleResourceManager
{
public:
	ModuleResourceManager();
	~ModuleResourceManager();

	uint Find(const char* asset_file)const;
	uint ImportFile(const char* new_asset_file);
	const Resource* Get(uint UID)const;
	Resource* Get(uint UID);
	Resource* CreateResource(ResourceType type )
private:
};

