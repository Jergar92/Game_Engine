#include "Application.h"
#include "Globals.h"
#include"ModuleMenuBar.h"
#include "ModuleScene.h"
#include "ModuleConsole.h"
#include"p2Defs.h"
#include "imgui\imgui.h"
#include "GameObject.h"
#include "ModuleFileSystem.h"
ModuleMenuBar::ModuleMenuBar(bool start_enabled):scene_go(nullptr), selected_go(nullptr)
{
	name = "Menu Bar";
}

ModuleMenuBar::~ModuleMenuBar()
{
}

bool ModuleMenuBar::Start()
{
	bool ret = true;

	LOG("Menu Bar Ready");
	

	return ret;


}


update_status ModuleMenuBar::GuiUpdate()
{

	if (App->console->GetShowConsole())
		App->console->Draw("Console Ready");

	if (GetAboutUsStatus())
		AboutUsWindow();

	
	if (!ShowEditor())
		return UPDATE_STOP;



	return UPDATE_CONTINUE;
}


bool ModuleMenuBar::CleanUp()
{
	bool ret = true;
	return ret;
}


bool ModuleMenuBar::ShowEditor()
{
	bool ret = true;
	ShowInspector();
	ShowHierarchy();
	ret = ShowMenuBar();

	return ret;
}

bool ModuleMenuBar::ShowInspector()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_Once);
	if (!ImGui::Begin("Inspector", &inspector, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return UPDATE_CONTINUE;
	}
	if (selected_go != nullptr)
	{
		selected_go->InspectorUpdate();
	}
	ImGui::End();
	return true;
}

bool ModuleMenuBar::ShowHierarchy()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_Once);
	if (!ImGui::Begin("Hierarchy", &hierarchy, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return UPDATE_CONTINUE;
	}
	if (scene_go != nullptr)
	{
		scene_go->GuiUpdate();
	}
	ImGui::End();
	return true;
}

bool ModuleMenuBar::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			
			ImGui::Separator();
			if (ImGui::MenuItem("Save"))
			{
				App->scene->SaveScene();
			}
			if (ImGui::MenuItem("Load"))
			{
				App->scene->LoadScene();
			}
			if (ImGui::MenuItem("Quit", "alt+f4"))
			{
				return false;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			
			if (ImGui::MenuItem("Console"))
			{
				Console();
				LOG("Create Console, no existing errors");
			}
			
			ImGui::Separator();

			if (ImGui::MenuItem("Configuration"))
			{
				Configuration();
				LOG("Create Configuration Window, no existing errors")

			}

			ImGui::Separator();
			if (ImGui::MenuItem("Profiler"))
			{
				Profiler();
				LOG("Create Profiler Window, no existing errors")

			}
			ImGui::Separator();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Documentation"))
			{
				ShellExecute(NULL, "open", "https://github.com/Jergar92/Game_Engine/wiki", NULL, NULL, SW_MINIMIZE);
				LOG("Open Link");
			}

			ImGui::Separator();


			if (ImGui::MenuItem("Download Latest"))
			{
				ShellExecute(NULL, "open", "https://github.com/Jergar92/Game_Engine/releases", NULL, NULL, SW_MINIMIZE);
				LOG("Open Link");
			}

			ImGui::Separator();


			if (ImGui::MenuItem("Report a bug"))
			{
				ShellExecute(NULL, "open", "https://github.com/Jergar92/Game_Engine/issues", NULL, NULL,SW_MINIMIZE);
				LOG("Open Link");
			}

			ImGui::Separator();

			if (ImGui::MenuItem("About us"))
			{
				AboutUs();
			}
				
			
			
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
		
	}
	
	return true;
}

void ModuleMenuBar::AboutUs()
{
	show_about_us = !show_about_us;
}

void ModuleMenuBar::AboutUsWindow()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowSize(ImVec2(510, 300), ImGuiCond_Once);
	
	ImGui::Begin("About Us", &show_about_us, window_flags);
	ImGui::Text("\n Name: Frog Engine. ");
	ImGui::Text("\n Description : this game engine is created for two student of the UPC, Enjoi It.");
	ImGui::Text("\n Creators : Sergio Saez.");
	
	if (ImGui::Selectable(" Andreu Rojas", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "https://github.com/Jergar92", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}
	
	if (ImGui::Selectable(" Sergio Saez", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "https://github.com/dreedcon", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}

	ImGui::Text("\n Licenses : ");
	
	if (ImGui::Selectable(" Mathgeolib v1.5", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "http://clb.demon.fi/MathGeoLib/nightly/", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}
    
	if (ImGui::Selectable(" Sdl v2.0.3", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "https://www.libsdl.org/", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}

	if (ImGui::Selectable(" imgui v.152 WIP", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}

	if (ImGui::Selectable(" JSON library writen in C", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open","https://github.com/nlohmann/json", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}

	if (ImGui::Selectable(" Assimp library v3.3.1 ", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "http://assimp.sourceforge.net/", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}

	if (ImGui::Selectable(" DevIL v1.4.0 ", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseDoubleClicked(0))
		{
			selected[3] = !selected[3];
		}
		ShellExecute(NULL, "open", "http://openil.sourceforge.net/", NULL, NULL, SW_MINIMIZE);
		LOG("Open Link");
	}
			
		ImGui::End();
}


bool ModuleMenuBar::GetAboutUsStatus()const
{
	return show_about_us;
}

bool ModuleMenuBar::Draw(bool open)
{
    if (open == true)
	{
		open = true;
	}
	else
	{
		open = false;
	}
	
	return  open;
}

void ModuleMenuBar::Console()
{
	App->console->ActiveConsole();
}

void ModuleMenuBar::Configuration()
{
	App->LoadConfigWindows();
}

void ModuleMenuBar::Profiler()
{
	App->LoadProfilerWindow();

}

void ModuleMenuBar::SetSceneGameObject(GameObject * set)
{
	scene_go = set;
}

void ModuleMenuBar::SetSelectedGameObject(GameObject * set)
{
	selected_go = set;
}
void ModuleMenuBar::LoadFile(const char* filter_extension, const char* from_dir)
{
	ImGui::OpenPopup("Load File");
	if (ImGui::BeginPopupModal("Load File", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		in_modal = true;

		ImGui::PushStyleVar(ImGuiStyleVar_ChildWindowRounding, 5.0f);
		ImGui::BeginChild("File Browser", ImVec2(3000, 300), true);
		DrawDirectoryRecursive(from_dir, filter_extension);
		ImGui::EndChild();
		ImGui::PopStyleVar();

		ImGui::PushItemWidth(250.f);
		/*
		if (ImGui::InputText("##file_selector", selected_file, FILE_MAX, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
			file_dialog = ready_to_close;

		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Ok", ImVec2(50, 20)))
			file_dialog = ready_to_close;
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(50, 20)))
		{
			file_dialog = ready_to_close;
			selected_file[0] = '\0';
		}
		*/
		ImGui::EndPopup();
	}
	else
		in_modal = false;
}

void ModuleMenuBar::DrawDirectoryRecursive(const char* directory, const char* filter_extension)
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;

	std::string dir((directory) ? directory : "");
	dir += "/";

	App->file_system->ListFiles("E:\\Andreu\\Repository\\Game_Engine\\Game\\Library", dirs, files);

	for (std::vector<std::string>::const_iterator it = dirs.begin(); it != dirs.end(); ++it)
	{
		if (ImGui::TreeNodeEx((dir + (*it)).c_str(), 0, "%s/", (*it).c_str()))
		{
			DrawDirectoryRecursive((dir + (*it)).c_str(), filter_extension);
			ImGui::TreePop();
		}
	}
	/*
	std::sort(files.begin(), files.end());

	for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); ++it)
	{
		const std::string& str = *it;

		bool ok = true;

		if (filter_extension && str.substr(str.find_last_of(".") + 1) != filter_extension)
			ok = false;

		if (ok && ImGui::TreeNodeEx(str.c_str(), ImGuiTreeNodeFlags_Leaf))
		{
			if (ImGui::IsItemClicked()) {
				sprintf_s(selected_file, FILE_MAX, "%s%s", dir.c_str(), str.c_str());

				if (ImGui::IsMouseDoubleClicked(0))
					file_dialog = ready_to_close;
			}

			ImGui::TreePop();
		}
	}
	*/
}