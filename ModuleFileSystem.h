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

	bool CreateNewFile(const char * path, char * buffer, int buffer_size, const char * directory);

	bool CreateOwnFile(const char * name, char * buffer,int buffer_int, const char * directory,const char* extension);
	JSON_Value* ParseJSONFile(const char * name, const char * directory);
	bool CreateJSONFile(const char * name, JSON_Value* value, const char * directory);

	int LoadFile(const char * name, char ** buffer);

	void LoadFile(const char* name, char** buffer,  const char * directory, const char* extension);

	bool CloneFile(const std::string path);

	bool ListFiles(const std::string path, Path& path_fill);
	bool UpdateFiles(const std::string path, Path& path_fill);

	bool CreateNewFolder(const std::string path, const char* name,std::string& full_path);

	std::string SetExtension(const char * name, const char * extension);
	std::string SetPathFile(const char * name, const char * directory);

	const char* GetMeshesFolder()const;
	const char* GetMaterialFolder()const;
	const char* GetAssetsFolder()const;
	const char* GetSettingsFolder()const;

private:
	bool CreateFolder(const char* name,  bool hide = false);
	std::string meshes;
	std::string materials;
	std::string assets;
	std::string settings;

};

