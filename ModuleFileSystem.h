#pragma once
#include "Module.h"

typedef struct json_value_t  JSON_Value;
struct Path;
struct PathList;
class ModuleFileSystem:public Module
{
public:
	ModuleFileSystem();
	~ModuleFileSystem();
	bool Awake(const JSONConfig& data);

	bool CreateNewFile(const char * path, char * buffer, int buffer_size, const char * directory);
	bool CreateOwnFile(const char * name, char * buffer,int buffer_int, const char * directory,const char* extension);
	JSON_Value * ParseJSONFile(const char * path);
	JSON_Value* ParseJSONFile(const char * name, const char * directory);
	bool CreateJSONFile(const char * name, JSON_Value* value, const char * directory);
	bool CreateJSONFile(JSON_Value * value, const char * path);
	void CreationTime(const char* file, char ** data);
	bool CreateNewFolder(const std::string& path, const char* name, std::string& full_path);


	int LoadFile(const char * path, const char * name, char ** buffer);
	int LoadFile(const char * name, char ** buffer);
	void LoadFile(const char* name, char** buffer,  const char * directory, const char* extension);
	bool CloneFile(const char* origin_path, const char* destination_path);


	bool ListFiles(const std::string& path, PathList& path_fill);

	bool FileExist(const char* file);
	bool FolderExist(const char* folder);
	bool RemoveFile(const char* file, bool directory = false);
	bool RemoveFile(const char * file, const char * path);
	bool CompareDates(const char* file, const char* date, char** buffer);
	std::string SetExtension(const char * name, const char * extension);
	std::string SetPathFile(const char * name, const char * directory);
	void RemplaceExtension(std::string&path, const std::string& new_extension);
	std::string ExtractFileName(const char* path);
	std::string ExtractName(const  char*path);
	std::string GetLibraryPath(const std::string&path_to_change, const char* path, const char* extension);

	const char* GetMeshesFolder()const;
	const char* GetMaterialFolder()const;
	const char* GetAssetsFolder()const;
	const char* GetAssetsMeshFolder()const;
	const char* GetAssetsTextFolder()const;
	const char* GetSettingsFolder()const;
	const char* GetPlayFolder()const;

private:
	bool CreateFolder(const char* name,  bool hide = false);
	std::string meshes;
	std::string a_textures;
	std::string a_meshes;

	std::string materials;
	std::string assets;
	std::string settings;
	std::string play;

	std::string str_path;
	std::string str_name;
};

