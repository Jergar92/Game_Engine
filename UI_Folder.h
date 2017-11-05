#pragma once
#include "UI_Windows.h"
#include <string>
#include <list>

struct Path
{
	Path();
	Path(std::string path, std::string name, std::string parent_path, bool directory);
	~Path();

	std::string path;
	std::string name;
	std::string parent_path;	
	std::list<Path> child;
	bool directory = true;
	void RemoveChild(const Path& child);

	void SetParentByPath(std::list<Path>& paths);
	void SetChild(const Path& child);
	void SetParent(Path* parent);
	bool operator ==(const Path& value);
	Path* parent;
};
struct PathList
{
	void OrderPath();
	bool PathExist(std::string cmp_path)const ;
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
	const char* GetFolderName()const;
	void SetUpFolders();
	void UpdateFiles();
	bool ShowFolder()const;

private:
	void DrawFolders(const Path& draw)const;


	void DrawFolderInfo();
	Path* show_folder;
	Path* folder_to_change;
	Path* item_selected;
	PathList path;
};

