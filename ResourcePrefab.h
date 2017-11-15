#pragma once
#include "Resource.h"
class ResourcePrefab :public Resource
{
public:
	ResourcePrefab(uint UID);
	~ResourcePrefab();
	void LoadInMemory();
	void Load();
	void UnLoadInMemory();
	void UnLoad();
	void InspectorUpdate();
};

