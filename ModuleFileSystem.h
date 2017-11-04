#pragma once
#include "Module.h"

typedef struct json_value_t  JSON_Value;
struct Path;
class ModuleFileSystem:public Module
{
public:
	ModuleFileSystem();
	~ModuleFileSystem();
	bool Awake(const JSONConfig& data);

	bool CreateOwnFile(const char * name, char * buffer,int buffer_int, const char * directory,const char* extension);
	JSON_Value* ParseJSONFile(const char * name, const char * directory);
	bool CreateJSONFile(const char * name, JSON_Value* value, const char * directory);

	void LoadFile(const char* name, char** buffer,  const char * directory, const char* extension);
	bool ListFiles(std::string path, Path& path_fill);
	std::string SetExtension(const char * name, const char * extension);

	std::string SetPathFile(const char * name, const char * directory);

	const char* GetMeshesFolder()const;
	const char* GetMaterialFolder()const;
	const char* GetAssetsFolder()const;
	const char* GetSettingsFolder()const;

private:
	void CreateFolder(const char* name,  bool hide = false);
	std::string meshes;
	std::string materials;
	std::string assets;
	std::string settings;

};

