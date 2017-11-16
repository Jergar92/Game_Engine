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
	Path(const std::string& path, const std::string& name,const std::string& parent_path, bool directory);
	~Path();
public:
	FileType SetType();
	void RemoveChild(Path* child);
	const std::string GetPath()const;
	void SetParentByPath(std::list<Path*>& paths);
	void SetChild(Path* child);
	void SetParent(Path* parent);
public:
	std::string path;
	std::string name;
	std::string parent_path;	
	std::list<Path*> child;
	bool directory = true;
	bool operator ==(const Path& value);
	FileType type = F_NONE;
	Path* parent;
};
struct PathList
{
	void CleanUp();
	void OrderPath();
	bool PathExist(const std::string& cmp_path)const ;
	void FillFiles(std::vector<const char*>& files,FileType especific);
	std::list<Path*>::const_iterator FindFolder(const std::string& show_folder_path)const;
	std::list<Path*> list;
private:
	std::vector<const char*> tmp_list;

};
class UI_Folder : public UI_Windows
{
public:
	UI_Folder(ModuleEditorWindows* my_editor);
	~UI_Folder();
	void CleanUp();
	bool Draw();
	bool ShowFolderEmpty() const;
	bool ItemSelectedEmpty() const;

	const char* GetFolderName()const;
	void SetUpFolders();
	void UpdateFiles();
	void FillFiles(std::vector<const char*>& files, FileType especific = F_NONE );
private:
	void DrawFolders(const Path* draw);

	void DrawFolderInfo();

	Path* folder_to_change;
	std::string show_folder;
	std::string item_selected;

	PathList path;
};

