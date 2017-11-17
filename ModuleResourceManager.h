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
	update_status PostUpdate(float dt);
	bool CleanUp();
	void LookForResources();
	Resource* CreateResource(ResourceType type, uint UID = -1);
	void DeleteResources();
	uint Find(const char* asset_file)const;

	uint ImportFile(const char* new_asset_file);
	void ReImport();
	const std::string GetLibraryPathFromOriginalPath(const char* original_path);
	uint ResourceWindows(ResourceType type);
	ResourceType GetResourceFromFile(const char* file);
	void GetAllResourcePath(ResourceType type, std::vector<std::string>& strings);
	const Resource* Get(uint UID)const;
	Resource* Get(uint UID);

	void SaveMetaResource(const char* path);
	void LoadMetaResource(const char* path);
private:
	bool need_to_delete = false;
	std::vector<std::string> files;
	std::map<uint, Resource*> resources;
	float time_update = 0.0f;
};

