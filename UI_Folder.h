#pragma once
#include "UI_Windows.h"
#include <string>
#include <vector>

struct Path
{
	Path();
	Path(std::string path, std::string name, Path* parent, bool directory);
	~Path();

	std::string path;
	std::string name;
	std::vector<Path> child;

	bool directory = true;
	Path* parent;
};
class UI_Folder : public UI_Windows
{
public:
	UI_Folder();
	~UI_Folder();
	void SetUpFolders();
	void CleanUp();

	bool Draw();
	void DrawFolders(const Path& draw)const;

	void DrawFolderInfo();
	Path* show_folfer;
	Path* folder_to_change;
	Path* item_selected;

	Path first_path;
};

