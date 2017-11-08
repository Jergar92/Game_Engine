#pragma once
#include "Globals.h"
#include "JSONConfig.h"
enum ResourceType
{
	R_NONE,
	R_TEXTURE,
	R_MESH
};
class Resource
{
public:
	Resource(uint UID,ResourceType type);
	virtual ~Resource();
	uint GetUID()const;
	bool IsLoadInMemory()const;
	ResourceType GetResourceType()const;
	virtual void SaveResource(JSONConfig& config)const;
	virtual void LoadResource(const JSONConfig& config);
	const std::string GetOriginalFile()const;
	const std::string GetLibraryFile()const;

protected:
	uint UID;
	uint load_count = 0;
	ResourceType type = R_NONE;
	std::string original_file;
	std::string library_file;
};

