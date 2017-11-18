#include "UI_Folder.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleEditorWindows.h"
#include "ModuleWindow.h"
#include "imgui/imgui.h"
#include <experimental\filesystem>
#define BUTTON_SPACE 80
UI_Folder::UI_Folder(ModuleEditorWindows* my_editor) :UI_Windows(my_editor) ,show_folder(std::string()), item_selected(std::string())
{
}


UI_Folder::~UI_Folder()
{

}

void UI_Folder::SetUpFolders()
{
	path.list.push_back(new Path(App->file_system->GetAssetsFolder(), "Assets", "", true));
	App->file_system->ListFiles((*path.list.begin())->path, path);
	path.OrderPath();
}

void UI_Folder::CleanUp()
{
	path.CleanUp();
	path.list.clear();
}

void UI_Folder::UpdateFiles()
{

	path.CleanUp();
	SetUpFolders();

}

void UI_Folder::FillFiles(std::vector<std::string>& files,FileType especific)
{
	path.FillFiles(files,especific);
}

bool UI_Folder::LoadWindow(char ** buffer)
{
	ImGui::OpenPopup("Load Window");
	static std::string selected;
	bool ret = false;
	if (ImGui::BeginPopupModal("Load Window", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{

		for (std::list<Path*>::const_iterator it = path.list.begin(); it != path.list.end(); it++)
		{
			if ((*it)->type!=F_JSON)
			{
				continue;
			}
			ImGuiWindowFlags tree_flags = 0;
			if (selected.compare((*it)->path) == 0)
			{
				tree_flags |= ImGuiTreeNodeFlags_Selected;
			}
			ImGui::TreeNodeEx((*it)->path.c_str(), tree_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
			if (ImGui::IsItemClicked())
			{
				selected = ((*it)->path);

			}
		}
	}

	ImGui::Separator();
	if (ImGui::Button("Select##mesh_select", ImVec2(120, 0)))
	{
		*buffer = new char[selected.length()+1];
		strcpy_s(*buffer, selected.length()+1, selected.c_str());
		ImGui::CloseCurrentPopup();
		ret = true;

	}
	ImGui::SameLine();
	if (ImGui::Button("Cancel", ImVec2(120, 0)))
	{
		ImGui::CloseCurrentPopup();
		ret = true;
	}
	ImGui::EndPopup();
	return ret;
}


bool UI_Folder::Draw()
{
	
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoResize;

	ImGui::SetNextWindowPos(ImVec2(0, SDL_GetWindowSurface(App->window->window)->h- 230), ImGuiCond_Always);

	ImGui::SetNextWindowSize(ImVec2(SDL_GetWindowSurface(App->window->window)->w, 230), ImGuiCond_Always);

	if (!ImGui::Begin("Folders", &active_draw, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
	}

	ImGui::Columns(2);
	std::list<Path*>::const_iterator it = path.list.begin();
	DrawFolders((*it));	
	ImGui::NextColumn();
	ImGui::BeginChild("FolderInfo", ImVec2(0, ImGui::GetWindowHeight()- BUTTON_SPACE), true);
	DrawFolderInfo();
	ImGui::EndChild();
	if(ImGui::Button("Load"))
	{
		if (item_selected.c_str() != "")
		{
			my_editor->WantToLoad(item_selected.c_str());
		}
	}
	ImGui::Columns(1);
	ImGui::End();
	
	return true;
}

void UI_Folder::DeleteFolders()
{
	if (delete_folder)
	{
		std::list<Path*>::const_iterator it = path.list.begin();
		while ( it != path.list.end())
		{
			if ((*it)->to_delete)
			{
				Path* item = *it;
				(*it)->parent->RemoveChild(item);
				App->file_system->RemoveFile(item->path.c_str(),item->directory);
				RELEASE(item);
				path.list.remove(*it++);
			}
			else
			{
				it++;
			}
		}
		delete_folder = false;
	}
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

void UI_Folder::DrawFolders(Path* draw) 
{
	if (path.list.empty())
	{
		return;
	}
	ImGuiWindowFlags tree_flags = 0;
	tree_flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
	if (draw->path == show_folder)
	{
		tree_flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (draw->child.empty())
		tree_flags |= ImGuiTreeNodeFlags_Leaf;

	bool node_open = ImGui::TreeNodeEx(draw->name.c_str(), tree_flags);
	if (ImGui::IsItemClicked())
	{
		show_folder = draw->path;
	} 
		//Asset protection	
	if (draw->parent != nullptr) {

		ImGui::PushID(draw->name.c_str());
		if (ImGui::BeginPopupContextItem("go_options"))
		{
			if (ImGui::Button("Delete"))
			{
				delete_folder = true;
				draw->ToDelete();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		ImGui::PopID();
	}

	if (node_open)
	{
		std::list<Path*>::const_iterator it = draw->child.begin();
		while (it != draw->child.end())
		{
			if ((*it)->directory) 
			{
				DrawFolders((*it));
			}
			it++;
		}
		ImGui::TreePop();
	}
}



void UI_Folder::DrawFolderInfo()
{
	if (path.list.empty())
	{
		return;
	}
	ImGui::Text("%s Contains:", show_folder.c_str());

	
	std::list<Path*>::const_iterator tmp = path.FindFolder(show_folder);
	if (tmp==path.list.end())
	{
		return;
	}
	std::list<Path*>::const_iterator it = (*tmp)->child.begin();
	while (it != (*tmp)->child.end())
	{
		if ((*it)->type == F_META)
		{
			it++;
			continue;
		}
		ImGuiWindowFlags tree_flags = 0;
		if (item_selected == (*it)->path)
		{
			tree_flags |= ImGuiTreeNodeFlags_Selected;
		}
		if ((*it)->child.empty())
			tree_flags |= ImGuiTreeNodeFlags_Leaf;

			bool node_open = ImGui::TreeNodeEx((*it)->name.c_str(), tree_flags);
			if (ImGui::IsItemClicked())
			{
				if ((*it)->directory)
				{
					if (ImGui::IsMouseDoubleClicked(0))
					{
						show_folder = (*it)->path;
					}
				}
				else
				{
					item_selected = (*it)->path;
					my_editor->SetSelectedResource(item_selected.c_str());
				}
			}
			ImGui::PushID((*it)->name.c_str());
			if (ImGui::BeginPopupContextItem("go_options"))
			{	
				if (ImGui::Button("Delete"))
				{
					(*it)->ToDelete();
					delete_folder = true;

					ImGui::CloseCurrentPopup();

				}
				ImGui::EndPopup();
			}
			ImGui::PopID();
			if (node_open)
			{
				ImGui::TreePop();
			}
		
		it++;
	}

	

}

Path::Path():path(std::string()),name(std::string()),parent(nullptr),directory(true)
{
}

Path::Path(const std::string& path, const std::string& name , const std::string& parent_path, bool directory) :path(path),name(name), parent_path(parent_path),directory(directory), parent(nullptr)
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

void Path::RemoveChild(Path* remove_child)
{
	child.remove(remove_child);
}

const std::string Path::GetPath() const
{
	return path;
}

void Path::SetParentByPath(std::list<Path*>& paths)
{
	std::list<Path*>::iterator it = paths.begin();
	for (std::list<Path*>::const_iterator it = paths.begin(); it != paths.end(); it++)
	{
		if ((*it)->path.compare(parent_path) != 0)
		{
			continue;
		}
		//if don't have parent set parent
		if (parent != nullptr)
		{
			if (parent->path.compare((*it)->path) != 0)
			{
				continue;
			}
			parent->RemoveChild(this);
		}
		SetParent((*it));

	}
}

void Path::SetChild(Path* set_child)
{
	child.push_back(set_child);
}

void Path::SetParent(Path * set_parent)
{
	parent = set_parent;
	parent->SetChild(this);
}

void Path::ToDelete()
{
	to_delete = true;
}

bool Path::operator==(const Path & value)
{
	return path==value.path;
}



void PathList::CleanUp()
{
	for (std::list<Path*>::iterator it = list.begin(); it != list.end(); it++)
	{
		RELEASE((*it));
	}
	list.clear();
}

void PathList::OrderPath()
{
	for (std::list<Path*>::iterator it = list.begin(); it != list.end(); it++)
	{
		(*it)->SetParentByPath(list);
	}
}

bool PathList::PathExist(const std::string& cmp_path)const 
{
	for (std::list<Path*>::const_iterator it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->path.compare(cmp_path) == 0)
		{
			return true;
		}
	}
	return false;
}

void PathList::FillFiles(std::vector<std::string>& files,FileType especific)
{
	tmp_list.clear();
	for (std::list<Path*>::iterator it = list.begin(); it != list.end(); it++)
	{
		if (!(*it)->directory&&especific == F_NONE && (*it)->type != F_META)
		{
			files.push_back((*it)->GetPath().c_str());
		}
		else if (!(*it)->directory&& (*it)->type == especific)
		{
			files.push_back((*it)->GetPath().c_str());
		}
	}
}

std::list<Path*>::const_iterator PathList::FindFolder(const std::string& show_folder_path)const
{
	std::list<Path*>::const_iterator ret;
	for (ret = list.begin(); ret != list.end(); ret++)
	{
		if ((*ret)->path.compare(show_folder_path) == 0)
		{
			return ret;
		}
	}
	return ret;
}


