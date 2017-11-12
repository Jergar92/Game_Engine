#include "UI_Folder.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleEditorWindows.h"
#include "imgui/imgui.h"
#include <experimental\filesystem>
#define BUTTON_SPACE 80
UI_Folder::UI_Folder() : show_folder(std::string()), item_selected(std::string()), folder_to_change(new Path())
{
}


UI_Folder::~UI_Folder()
{

}

void UI_Folder::SetUpFolders()
{
	path.list.push_back(Path(App->file_system->GetAssetsFolder(), "Assets", "", true));
	App->file_system->ListFiles(path.list.begin()->path, path);
	path.OrderPath();
}

void UI_Folder::CleanUp()
{
	path.list.clear();
}

void UI_Folder::UpdateFiles()
{

	path.list.clear();
	SetUpFolders();
	path.OrderPath();

}

std::vector<std::string>UI_Folder::ReturnFiles(FileType especific)
{
	return path.ReturnFiles(especific);
}


bool UI_Folder::Draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiCond_Once);
	if (!ImGui::Begin("Folders", &active_draw, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
	}

	ImGui::Columns(2);
	std::list<Path>::const_iterator it = path.list.begin();
	DrawFolders(it._Ptr->_Myval);	
	ImGui::NextColumn();
	ImGui::BeginChild("FolderInfo", ImVec2(0, ImGui::GetWindowHeight()- BUTTON_SPACE), true);
	DrawFolderInfo();
	ImGui::EndChild();
	if(ImGui::Button("Load"))
	{
		if (item_selected.c_str() != "")
		{
			App->editor_window->WantToLoad(item_selected.c_str());
		}
	}
	ImGui::Columns(1);
	ImGui::End();
	
	return true;
}


bool UI_Folder::ItemSelectedEmpty() const
{
	return item_selected.empty();
}

bool UI_Folder::ShowFolderEmpty()const
{
	return show_folder.empty();
}

const char * UI_Folder::GetFolderName() const
{
	return show_folder.c_str();
}

void UI_Folder::DrawFolders(const Path& draw) 
{
	ImGuiWindowFlags tree_flags = 0;
	tree_flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
	if (draw.path == show_folder)
	{
		tree_flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (draw.child.empty())
		tree_flags |= ImGuiTreeNodeFlags_Leaf;

	bool node_open = ImGui::TreeNodeEx(draw.name.c_str(), tree_flags);
	if (ImGui::IsItemClicked())
	{
	
		show_folder = draw.path;

	}
	/*
	if (ImGui::BeginPopupContextItem("Folder Options"))
	{
		ImGui::EndPopup();
	}
	*/
	if (node_open)
	{
		std::list<Path>::const_iterator it = draw.child.begin();
		while (it != draw.child.end())
		{
			if ((it)->directory) 
			{
				DrawFolders(*(it));
			}
			it++;
		}
		ImGui::TreePop();
	}
}



void UI_Folder::DrawFolderInfo()
{
	ImGui::Text("%s Contains:", show_folder.c_str());


	std::list<Path>::const_iterator tmp = path.FindFolder(show_folder);
	if (tmp==path.list.end())
	{
		return;
	}
	std::list<Path>::const_iterator it = tmp->child.begin();
	while (it != tmp->child.end())
	{
		if (it->type == F_META)
		{
			it++;
			continue;
		}
		ImGuiWindowFlags tree_flags = 0;
		if (item_selected == it->path)
		{
			tree_flags |= ImGuiTreeNodeFlags_Selected;
		}
		if (it->child.empty())
			tree_flags |= ImGuiTreeNodeFlags_Leaf;

			bool node_open = ImGui::TreeNodeEx(it->name.c_str(), tree_flags);

			if (node_open)
			{
				if (ImGui::IsItemClicked() )
				{
					if (it->directory)
					{
						if (ImGui::IsMouseDoubleClicked(0))
						{
							show_folder = it->path;
						}
					}
					else
					{
						item_selected = it->path;
					}
				}

				ImGui::TreePop();
			}
		
		it++;
	}

	

}
void UI_Folder::ToLoad(const char * path)
{
	std::string extension_string = path;
	std::size_t found = extension_string.find_last_of('.');
	if (extension_string.substr(found + 1) == "json")
	{
		App->editor_window->ToLoad(path, LoadFile::LOAD_SCENE);
	}
	else if (extension_string.substr(found + 1) == "png" || extension_string.substr(found + 1) == "jpg" || extension_string.substr(found + 1) == "dds")
	{
		App->editor_window->ToLoad(path, LoadFile::LOAD_TEXTURE);

	}
	else
	{
		App->editor_window->ToLoad(path, LoadFile::LOAD_MESH);

	}
}
Path::Path():path(std::string()),name(std::string()),parent(nullptr),directory(true)
{
}

Path::Path(std::string path,std::string name , std::string parent_path, bool directory) :path(path),name(name), parent_path(parent_path),directory(directory), parent(nullptr)
{
	type = SetType();
}

Path::~Path()
{
	child.clear();
	parent = nullptr;

}

FileType Path::SetType()
{
	if (directory)
	{
		return F_DIRECTORY;
	}
	else
	{
		std::size_t found = path.find_last_of('.');
		std::string extension = path.substr(found + 1);
		if (_stricmp(extension.c_str(), "png") == 0
			|| _stricmp(extension.c_str(), "jpg") == 0
			|| _stricmp(extension.c_str(), "dds") == 0
			|| _stricmp(extension.c_str(), "tga") == 0)
		{
			return F_TEXTURE;
		}
		else if (_stricmp(extension.c_str(), "json") == 0)
		{
			std::size_t found = path.find("meta.json");
			if (found != std::string::npos)
			{
				return F_META;

			}
			else
			{
				return F_JSON;

			}
		}
		else if (_stricmp(extension.c_str(), "obj") == 0
			|| _stricmp(extension.c_str(), "fbx") == 0)
		{
			return F_MESH;
		}
		else
		{
			return F_NONE;
		}
	}
}

void Path::RemoveChild(const Path & remove_child)
{
	child.remove(remove_child);
}

const std::string Path::GetPath() const
{
	return path;
}

void Path::SetParentByPath(std::list<Path>& paths)
{
	std::list<Path>::iterator it = paths.begin();
	for (std::list<Path>::const_iterator it = paths.begin(); it != paths.end(); it++)
	{
		if (it->path.compare(parent_path) != 0)
		{
			continue;
		}
		//if don't have parent set parent
		if (parent != nullptr)
		{
			if (parent->path.compare(it->path) != 0)
			{
				continue;
			}
			parent->RemoveChild(*(this));
		}
		SetParent(&(it)._Ptr->_Myval);

	}
}

void Path::SetChild(const Path & set_child)
{
	child.push_back(set_child);
}

void Path::SetParent(Path * set_parent)
{
	parent = set_parent;
	parent->SetChild(*(this));
}

bool Path::operator==(const Path & value)
{
	return path==value.path;
}

void PathList::OrderPath()
{
	for (std::list<Path>::iterator it = list.begin(); it != list.end(); it++)
	{
		(it)->SetParentByPath(list);
	}
}

bool PathList::PathExist(std::string cmp_path)const 
{
	for (std::list<Path>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		if (it->path.compare(cmp_path) == 0)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::string>PathList::ReturnFiles(FileType especific)
{
	std::vector<std::string> path_list;
	for (std::list<Path>::iterator it = list.begin(); it != list.end(); it++)
	{
		if (!it->directory&&especific==F_NONE&&it->type != F_META)
			path_list.push_back(it->GetPath());
		else if (!it->directory&&it->type == especific)
		{
			path_list.push_back(it->GetPath());
		}
	}
	return path_list;
}

std::list<Path>::const_iterator PathList::FindFolder(std::string show_folder_path)const
{
	std::list<Path>::const_iterator ret;
	for (ret = list.begin(); ret != list.end(); ret++)
	{
		if (ret->path.compare(show_folder_path) == 0)
		{
			return ret;
		}
	}
	return ret;
}


