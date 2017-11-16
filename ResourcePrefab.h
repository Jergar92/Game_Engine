#pragma once
#include "Resource.h"
class ResourcePrefab :public Resource
{
public:
	ResourcePrefab(uint UID);
	~ResourcePrefab();
	void LoadInMemory();

	void InspectorUpdate();
	void SaveResource(JSONConfig& data)const;
	void LoadResource(const JSONConfig& data);

};

