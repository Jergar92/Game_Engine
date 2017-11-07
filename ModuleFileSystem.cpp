#include "Application.h"
#include "Globals.h"
#include "ModuleFileSystem.h"
#include "Parson\parson.h"

#include "p2Defs.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <experimental/filesystem>

#include "UI_Folder.h"

#define ASSETS_FOLDER "Assets"
#define LIBRARY_FOLDER "Library"
#define MESHES_FOLDER "Library/Meshes"
#define MATERIAL_FOLDER "Library/Material"
#define PLAY_FOLDER "Library/Play"

#define SETTINGS_FOLDER "Settings"


ModuleFileSystem::ModuleFileSystem()
{
	name = "File System";
	meshes = MESHES_FOLDER;
	assets = ASSETS_FOLDER;
	materials = MATERIAL_FOLDER;
	settings = SETTINGS_FOLDER;
	play = PLAY_FOLDER;
	CreateFolder(assets.c_str());
	CreateFolder(LIBRARY_FOLDER);
	CreateFolder(meshes.c_str(), true);
	CreateFolder(materials.c_str(), true);
	CreateFolder(play.c_str(), true);

	CreateFolder(settings.c_str());
}


ModuleFileSystem::~ModuleFileSystem()
{
	
}

bool ModuleFileSystem::Awake(const JSONConfig& data)
{
	bool ret = true;



	//Assets 
	//Library / Meshes
	//Library / Materials
	//Settings
	return ret;
}



bool ModuleFileSystem::CreateNewFile(const char* path, char* buffer, int buffer_size, const char* directory)
{
	bool ret = true;
	std::string complete_path = PATH(directory, path);


	std::ofstream save_file(complete_path.c_str(), std::ofstream::binary);

	if (save_file.good())
	{
		save_file.write(buffer, buffer_size);
		save_file.close();
	}
	else
	{
		LOG("Error on creating the file")
			ret = false;
	}
	return ret;
}


bool ModuleFileSystem::CreateOwnFile(const char* name, char* buffer,int buffer_size, const char* directory,const char* extension)
{
	bool ret = true;
	std::string file_name = FILE_EXTENSION(name, extension);
	std::string complete_path= PATH(directory, file_name.c_str());

	std::ofstream save_file(complete_path.c_str(), std::ofstream::binary);

	if (save_file.good())
	{
		LOG("Save custom format with:\n name = %s \n buffer size %i\n complete path= %s", file_name.c_str(), buffer_size, complete_path.c_str());

		save_file.write(buffer, buffer_size);
		save_file.close();
	}
	else
	{
		LOG("Error on creating the file")
		ret = false;
	}
	return ret;
}

JSON_Value * ModuleFileSystem::ParseJSONFile(const char * name, const char * directory)
{
	std::string complete_path = PATH(directory, name);

	JSON_Value * ret = json_parse_file(complete_path.c_str());
	return ret;
}
JSON_Value * ModuleFileSystem::ParseJSONFile(const char * path)
{

	JSON_Value * ret = json_parse_file(path);
	return ret;
}
bool ModuleFileSystem::CreateJSONFile(const char * name, JSON_Value * value, const char * directory)
{
	std::string complete_path = PATH(directory, name);

	return json_serialize_to_file(value, complete_path.c_str());;
}
bool ModuleFileSystem::CreateJSONFile( JSON_Value * value, const char * path)
{

	return json_serialize_to_file(value, path);;
}
int ModuleFileSystem::LoadFile(const char * name, char ** buffer)
{
	std::ifstream load_file(name, std::ifstream::binary);
	int size = 0;

	if (load_file.good())
	{

		load_file.seekg(0, load_file.end);
		size = load_file.tellg();
		load_file.seekg(0, load_file.beg);

		*buffer = new char[size];

		load_file.read(*buffer, size);

		load_file.close();

	}
	else
	{
		LOG("Error on Load the file")
	}
	return size;
}
void ModuleFileSystem::LoadFile(const char * name, char ** buffer, const char * directory, const char * extension)
{
	std::string file_name = FILE_EXTENSION(name, extension);
	std::string complete_path = PATH(directory, file_name.c_str());

	std::ifstream load_file(complete_path.c_str(), std::ifstream::binary);
	int size = 0;

	if (load_file.good())
	{
	
		load_file.seekg(0, load_file.end);
		std::streamsize size = load_file.tellg();
		load_file.seekg(0, load_file.beg);

		*buffer = new char[size];

		load_file.read(*buffer, size);

		load_file.close();
		
	}
	else
	{
		LOG("Error on Load the file")
	}

}
bool ModuleFileSystem::CloneFile(const std::string path)
{
	char* buffer = nullptr;
	namespace file_system = std::experimental::filesystem;
	std::string name(file_system::path(path).filename().string());
	//Load the file
	int size= LoadFile(path.c_str(), &buffer);
	CreateNewFile(name.c_str(), buffer, size, GetAssetsFolder());
	RELEASE_ARRAY(buffer);
	return true;
}
std::string ModuleFileSystem::SetExtension(const char * name, const char * extension)
{
	
	std::string file_name(FILE_EXTENSION(name, extension));
	return file_name;
}
std::string ModuleFileSystem::SetPathFile(const char * name, const char * directory)
{
	
	std::string file_name(PATH(directory, name));
	return file_name;
}

void ModuleFileSystem::RemplaceExtension(std::string & path, const std::string & new_extension)
{
	std::string::size_type size = path.rfind('.', path.length());

	if (size != std::string::npos) {
		path.replace(size + 1, new_extension.length(), new_extension);
	}
}

std::string ModuleFileSystem::ExtractName(const std::string & path)
{
	namespace file_system = std::experimental::filesystem;
	std::string name(file_system::path(path).stem().string());
	return name;
}

std::string ModuleFileSystem::GetLibraryPath(const std::string & path_to_change,const char* directory,const char* extension)
{
	std::string name= ExtractName(path_to_change);
	RemplaceExtension(name, std::string(extension));
	std::string file_name(PATH(directory, name.c_str()));
	return file_name;

}

bool ModuleFileSystem::ListFiles(const std::string parent_path, PathList& path_fill)
{
	for (std::experimental::filesystem::directory_iterator::value_type item : std::experimental::filesystem::directory_iterator(parent_path))
	{
		std::string str_path = item.path().string().c_str();

		std::string str_name = item.path().filename().generic_string();
		
		bool directory = false;
		std::string path = str_path;
		if (item.status().type() == std::experimental::filesystem::file_type::directory)
		{
			ListFiles(path, path_fill);
			directory = true;

		}
		Path new_directory(path, str_name, parent_path, directory);
		path_fill.list.push_back(new_directory);
	
		
	}
	return true;
}


bool ModuleFileSystem::CreateNewFolder(const std::string path, const char * name,std::string& full_path)
{
	full_path=(PATH(path.c_str(), name));
	return CreateFolder(full_path.c_str());
}



const char * ModuleFileSystem::GetMeshesFolder()const
{
	return meshes.c_str();
}

const char * ModuleFileSystem::GetMaterialFolder()const
{
	return materials.c_str();
}

const char * ModuleFileSystem::GetAssetsFolder()const
{
	return assets.c_str();
}

const char * ModuleFileSystem::GetSettingsFolder() const
{
	return settings.c_str();
}

const char * ModuleFileSystem::GetPlayFolder() const
{
	return play.c_str();
}

bool ModuleFileSystem::CreateFolder(const char * name, bool hide)
{

	if (CreateDirectory(name, NULL))
	{
		if (hide)
		{
			SetFileAttributes(name, FILE_ATTRIBUTE_HIDDEN);
		}
		return true;
	}
	else
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{

			LOG("Directory (%s) already exists", name);
		}
		return false;

	}
}

