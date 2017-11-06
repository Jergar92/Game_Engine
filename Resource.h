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

	virtual void Save(JSONConfig& config)const;
	virtual void Load(const JSONConfig& config);
protected:
	uint UID;
	uint load_count = 0;
};

