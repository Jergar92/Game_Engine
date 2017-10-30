#pragma once
#include "Module.h"

class ModuleFileSystem:public Module
{
public:
	ModuleFileSystem();
	~ModuleFileSystem();
	bool Awake(const JSONConfig& data);
	bool CreateOwnFile(const char * name, char * buffer,int buffer_int, const char * directory,const char* extension);

	const char* GetMeshesFolder()const;
	const char* GetMaterialFolder()const;
	const char* GetAssetsFolder()const;

private:
	void CreateFolder(const char* name,  bool hide = false);
	std::string meshes;
	std::string materials;
	std::string assets;
};

