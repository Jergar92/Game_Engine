#pragma once
#include "UI_Windows.h"
#include <string>
#include <list>
#include <vector>
enum FileType
{
	F_NONE,
	F_MESH,
	F_TEXTURE,
	F_META,
	F_JSON,
	F_DIRECTORY
};
struct Path
{
	Path();
	Path(std::string path, std::string name, std::string parent_path, bool directory);
	~Path();
public:
	FileType SetType();
	void RemoveChild(const Path& child);
	const std::string GetPath()const;
	void SetParentByPath(std::list<Path>& paths);
	void SetChild(const Path& child);
	void SetParent(Path* parent);
public:
	std::string path;
	std::string name;
	std::string parent_path;	
	std::list<Path> child;
	bool directory = true;
	bool operator ==(const Path& value);
	FileType type = F_NONE;
	Path* parent;
};
struct PathList
{
	void OrderPath();
	bool PathExist(std::string cmp_path)const ;
	std::vector<std::string> ReturnFiles(FileType especific);
	std::list<Path>::const_iterator FindFolder(std::string show_folder_path)const;
	std::list<Path> list;

};
class UI_Folder : public UI_Windows
{
public:
	UI_Folder();
	~UI_Folder();
	void CleanUp();
	bool Draw();
	bool ShowFolderEmpty() const;
	bool ItemSelectedEmpty() const;

	const char* GetFolderName()const;
	void SetUpFolders();
	void UpdateFiles();
	std::vector<std::string>ReturnFiles(FileType especific = F_NONE);
private:
	void DrawFolders(const Path& draw);

	void DrawFolderInfo();
	void ToLoad(const char* path);

	Path* folder_to_change;
	std::string show_folder;
	std::string item_selected;

	PathList path;
};

