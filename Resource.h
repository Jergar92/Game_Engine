#pragma once
#include "Globals.h"
#include "JSONConfig.h"
enum ResourceType
{
	R_NONE,
	R_TEXTURE,
	R_MESH,
	R_PREFAB
};
class Resource
{
public:
	Resource(uint UID,ResourceType type);
	virtual ~Resource();
	uint GetUID()const;
	bool IsLoadInMemory()const;
	virtual void LoadInMemory();
	virtual void Load();
	virtual void UnLoadInMemory();
	virtual void UnLoad();
	virtual void InspectorUpdate();
	ResourceType GetResourceType()const;
	const std::string& GetOriginalFile()const;
	const std::string& GetLibraryFile()const;
	const std::string& GetMetaJsonFile()const;

	void SetOriginalFile(const char* set);
	void SetOriginalFile(const char * set, const char * extension);
	void SetLibraryFile(const char* set,const char* extension);
	void SetMetaFile(const char* set);
	virtual void ReImport();
	virtual void SaveResource(JSONConfig& config)const;
	virtual void LoadResource(const JSONConfig& config);


protected:
	uint UID;
	uint load_count = 0;
	ResourceType type = R_NONE;
	std::string original_file;
	std::string library_file;
	std::string meta_file;
};

