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
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	uint ResourceWindows(ResourceType type);
	bool CleanUp();

	Resource* CreateResource(ResourceType type, uint UID = -1);

	const Resource* Get(uint UID)const;
	Resource* Get(uint UID);
	uint Find(const char* asset_file)const;
	uint ImportFile(const char* new_asset_file);

private:

	void LookForResources();
	void DeleteResources();
	ResourceType GetResourceFromFile(const char* file)const;
	bool ReImport(Resource * resource);



	

	void SaveMetaResource(const char* path);
	void LoadMetaResource(const char* path);
private:
	bool need_to_delete = false;
	std::vector<std::string> files;
	std::map<uint, Resource*> resources;
	float time_update = 0.0f;
};

