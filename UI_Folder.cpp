#include "UI_Folder.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "imgui/imgui.h"
#include <experimental\filesystem>

UI_Folder::UI_Folder() : show_folder(new Path()), item_selected(new Path()), folder_to_change(new Path())
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
	//first_path.child.clear();

	path.list.clear();
	App->file_system->UpdateFiles(path.list.begin()->path, path);
	path.OrderPath();

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
	DrawFolderInfo();
	ImGui::Columns(1);
	ImGui::End();
	if (show_folder!=folder_to_change)
	{

		show_folder = folder_to_change;
	}
	return true;
}

bool UI_Folder::ShowFolder()const
{
	return show_folder->path!="";
}

const char * UI_Folder::GetFolderName() const
{
	return show_folder->path.c_str();
}

void UI_Folder::DrawFolders(const Path& draw) const
{
	ImGuiWindowFlags tree_flags = 0;
	if (draw.child.empty())
		tree_flags |= ImGuiTreeNodeFlags_Leaf;
	tree_flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;

	bool node_open = ImGui::TreeNodeEx(draw.name.c_str(), tree_flags);
	if (ImGui::IsItemClicked())
	{
	
			*folder_to_change = draw;
		
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
	ImGui::Text("%s Contains:", show_folder->name.c_str());


	std::list<Path>::const_iterator it = show_folder->child.begin();

	while (it != show_folder->child.end())
	{
		ImGuiWindowFlags tree_flags = 0;

		if (it->child.empty())
			tree_flags |= ImGuiTreeNodeFlags_Leaf;
		bool node_open = ImGui::TreeNodeEx(it->name.c_str(), tree_flags);

		if (node_open)
		{
			if (ImGui::IsItemClicked() && !it->directory) 
			{
				*item_selected = *(it);
			}

			ImGui::TreePop();
		}
		it++;

	}
}

Path::Path():path(std::string()),name(std::string()),parent(nullptr),directory(true)
{
}

Path::Path(std::string path,std::string name , std::string parent_path, bool directory) :path(path),name(name), parent_path(parent_path),directory(directory), parent(nullptr)
{

}

Path::~Path()
{
	child.clear();
	parent = nullptr;

}

void Path::RemoveChild(const Path & remove_child)
{
	child.remove(remove_child);
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

std::list<Path>::const_iterator PathList::FindFolder(std::string show_folder_path)const
{
	for (std::list<Path>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		if (it->path.compare(show_folder_path) == 0)
		{
			return it;
		}
	}
	return std::list<Path>::const_iterator();
}
