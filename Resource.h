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
	virtual void CleanUp();

	void ToDelete();

	ResourceType GetResourceType()const;
	const std::string GetOriginalFile()const;
	const std::string GetLibraryFile()const;
	const std::string GetMetaJsonFile()const;
	const std::string GetCreationTime()const;
	const std::string GetOrignalName()const;


	void SetDateOfCreation(const char * set);
	void SetOriginalFile(const char* set);
	void SetOriginalName(const char * set);
	void SetOriginalFile(const char * set, const char * extension);
	void SetLibraryFile(const char* set,const char* extension);
	void SetMetaFile(const char* set);

	bool GetDelete()const;

	virtual void ReImport();
	virtual void SaveResource(JSONConfig& config)const;
	virtual void LoadResource(const JSONConfig& config);


protected:
	uint UID = 0;
	uint load_count = 0;
	ResourceType type = R_NONE;
	std::string creation_time;
	std::string original_file;
	std::string original_name;
	std::string library_file;
	std::string meta_file;
	bool to_delete = false;
};

