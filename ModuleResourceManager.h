#pragma once
#include "Module.h"
#include "Globals.h"
#include "Resource.h"
#include <map>
class ModuleResourceManager : public Module
{
public:
	ModuleResourceManager();
	~ModuleResourceManager();

	update_status Update(float dt);

	uint Find(const char* asset_file)const;
	uint ImportFile(const char* new_asset_file);
	ResourceType GetResourceFromFile(const char* file);
	const Resource* Get(uint UID)const;
	Resource* Get(uint UID);
	Resource* CreateResource(ResourceType type,uint UID=-1);
private:
	std::map<uint, Resource*> resources;
	float time_update = 0.0f;
};

