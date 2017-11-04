#include "UI_Folder.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "imgui/imgui.h"
#include <experimental\filesystem>

UI_Folder::UI_Folder() : show_folfer(new Path()), item_selected(new Path()), folder_to_change(new Path())
{
}


UI_Folder::~UI_Folder()
{
}

void UI_Folder::SetUpFolders()
{
	first_path=Path(App->file_system->GetAssetsFolder(),"Assets", nullptr,true);
	App->file_system->ListFiles(first_path.path, first_path);
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
	DrawFolders(first_path);
	ImGui::NextColumn();
	DrawFolderInfo();
	ImGui::Columns(1);
	ImGui::End();
	if (show_folfer != folder_to_change)
		show_folfer = folder_to_change;
	return true;
}

void UI_Folder::DrawFolders(const Path& draw) const
{
	ImGuiWindowFlags tree_flags = 0;

	if (draw.child.empty())
		tree_flags |= ImGuiTreeNodeFlags_Leaf;
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
		std::vector<Path>::const_iterator it = draw.child.begin();
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
	std::vector<Path>::const_iterator it = show_folfer->child.begin();
	while (it != show_folfer->child.end())
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

Path::Path(std::string path,std::string name ,Path * parent, bool directory) :path(path),name(name),parent(parent),directory(directory)
{

}
