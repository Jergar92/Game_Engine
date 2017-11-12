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
	bool Start();

	update_status Update(float dt);
	void LookForResources();
	uint Find(const char* asset_file)const;

	uint ImportFile(const char* new_asset_file);
	const std::string GetLibraryPathFromOriginalPath(const char* original_path);

	ResourceType GetResourceFromFile(const char* file);

	const Resource* Get(uint UID)const;
	Resource* Get(uint UID);
	Resource* CreateResource(ResourceType type,uint UID=-1);

	void SaveMetaResource(const char* path);
	void LoadMetaResource(const char* path);
private:
	std::map<uint, Resource*> resources;
	float time_update = 0.0f;
};

