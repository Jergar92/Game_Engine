#include "Application.h"
#include "Globals.h"
#include"ModuleEditorWindows.h"
#include "ModuleScene.h"
#include"p2Defs.h"
#include "ModuleCamera.h"
#include "imgui\imgui.h"
#include "GameObject.h"
#include "ModuleFileSystem.h"
#include "Component.h"
#include "UI_Windows.h"
#include "UI_Inspector.h"
#include "UI_Hierarchy.h"
#include "UI_About.h"
#include "UI_Console.h"
#include "UI_Folder.h"
#include "UI_Play.h"

ModuleEditorWindows::ModuleEditorWindows(bool start_enabled)
{
	name = "Editor Windows";
	ui_play = new UI_Play();
	ui_inspector = new UI_Inspector();
	ui_hierarchy = new UI_Hierarchy();
	ui_about = new UI_About();
	ui_console = new UI_Console();
	ui_folder = new UI_Folder();

	ui_windows.push_back(ui_play);
	ui_windows.push_back(ui_inspector);
	ui_windows.push_back(ui_hierarchy);
	ui_windows.push_back(ui_about);
	ui_windows.push_back(ui_console);
	ui_windows.push_back(ui_folder);

}

ModuleEditorWindows::~ModuleEditorWindows()
{
}

bool ModuleEditorWindows::Start()
{
	bool ret = true;

	ui_folder->SetUpFolders();
	LOG("Menu Bar Ready");
	

	return ret;


}

update_status ModuleEditorWindows::PreUpdate(float dt)
{
	if (want_to_update)
	{
		UpdateFiles();
		want_to_update = false;
	}


	return UPDATE_CONTINUE;
}

update_status ModuleEditorWindows::PostUpdate(float dt)
{

	if (want_to_save)
	{
		App->scene->SaveScene(path_to_save.c_str());
		want_to_save = false;
	}

	if (want_to_load)
	{
		App->scene->LoadScene(path_to_load.c_str());
		want_to_load = false;
	}
	return UPDATE_CONTINUE;
}


update_status ModuleEditorWindows::GuiUpdate()
{



	
	bool ret = ShowMenuBar();
	for (int i = 0; i < ui_windows.size() && ret == true; i++)
	{
		if (ui_windows[i]->IsActive())
			ret = ui_windows[i]->Draw();
	}

	if (!ret)
		return UPDATE_STOP;



	return UPDATE_CONTINUE;
}


bool ModuleEditorWindows::CleanUp()
{
	bool ret = true;
	for (int i = 0; i < ui_windows.size() && ret == true; i++)
	{
		ui_windows[i]->CleanUp();
	}
	RELEASE(ui_inspector);
	RELEASE(ui_hierarchy);
	RELEASE(ui_about);
	RELEASE(ui_console);
	RELEASE(ui_folder);

	ui_windows.clear();
	return ret;
}




bool ModuleEditorWindows::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			
			ImGui::Separator();
			if (ImGui::MenuItem("Save"))
			{
				std::string path = App->file_system->GetAssetsFolder();
			
				WantToSave("scene.json", path.c_str());

			}
			if (ImGui::MenuItem("Load"))
			{
				std::string path = App->file_system->GetAssetsFolder();
				
			
				WantToLoad("try.json", path.c_str());

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
				ui_console->ChangeActive();
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
			if (ImGui::MenuItem("Hierarchy"))
			{
				ui_hierarchy->ChangeActive();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Inspector"))
			{
				ui_inspector->ChangeActive();
			}

			ImGui::Separator();
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::MenuItem("Show Raycast"))
				{
					if (!App->camera->GetRaycast())
					{
						App->camera->EnableRaycast();
						LOG("Draw Raycast enable");
					}
					else if (App->camera->GetRaycast())
					{
						App->camera->EnableRaycast();
						LOG("Draw Raycast Disable")
					}	
				}
             ImGui::EndMenu();
			}

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
				ui_about->ChangeActive();
			}
				
			
			
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
		
	}
	
	return true;
}

void ModuleEditorWindows::Configuration()
{
	App->LoadConfigWindows();
}

void ModuleEditorWindows::Profiler()
{
	App->LoadProfilerWindow();

}

void ModuleEditorWindows::SetSceneGameObject(GameObject * set)
{
	ui_hierarchy->SetSceneGameObject(set);
}

GameObject * ModuleEditorWindows::GetSelectedGameObject() const
{
	return ui_inspector->GetSelected();
}

void ModuleEditorWindows::SetSelectedGameObject(GameObject * set)
{
	ui_inspector->SetSelectedGameObject(set);
}
void ModuleEditorWindows::AddLog(const char * fmt, ...)
{
	if (ui_console != nullptr)
		ui_console->AddLog(fmt);
}
void ModuleEditorWindows::ToLoad(const char * path, LoadFile load)
{
	wait_load = true;
	path_to_load = path;
	//next_load = load;
}
void ModuleEditorWindows::WantToLoad(const char * name, const char * path)
{
	want_to_load = true;
	path_to_load = App->file_system->SetPathFile(name, path);
}
void ModuleEditorWindows::WantToSave(const char * name, const char * path)
{
	want_to_save = true;
	path_to_save = App->file_system->SetPathFile(name, path);
}
std::vector<std::string> ModuleEditorWindows::ReturnFiles(FileType especific)
{
	return ui_folder->ReturnFiles(especific);
}
void ModuleEditorWindows::WantToUpdate()
{
	want_to_update = true;
}
void ModuleEditorWindows::UpdateFiles()
{
	ui_folder->UpdateFiles();

}
void ModuleEditorWindows::Load()
{

	switch (next_load)
	{
	case LOAD_MESH:
	{
		if (ui_inspector->selected_go == nullptr)
		{
			break;
		}
		ComponentMesh* item = (ComponentMesh*)ui_inspector->selected_go->FindComponent(ComponentType::MESH);
		if (item == nullptr)
			item = (ComponentMesh*)ui_inspector->selected_go->CreateComponent(ComponentType::MESH);
		std::string libray_path = App->file_system->ExtractName(path_to_load);
		//App->importer->Load()
		App->importer->LoadMesh(libray_path.c_str(), item);
	}
		break;
	case LOAD_TEXTURE:
	{
		if(ui_inspector->selected_go==nullptr)
		{
			break;
		}
		ComponentMeshRenderer* item = (ComponentMeshRenderer*)ui_inspector->selected_go->FindComponent(ComponentType::MESH_RENDER);
		if (item == nullptr)
			item = (ComponentMeshRenderer*)ui_inspector->selected_go->CreateComponent(ComponentType::MESH_RENDER);
		std::string libray_path = App->file_system->ExtractName(path_to_load);
	//	App->importer->LoadTexture(libray_path.c_str(), item);
	}
		break;
	case LOAD_SCENE:	

		break;
	default:
		break;
	}

	next_load = LOAD_NONE;
	wait_load = false;
}
/*
void ModuleEditorWindows::LoadFile(const char* filter_extension, const char* from_dir)
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
		
		ImGui::EndPopup();
	}
	else
		in_modal = false;
}

void ModuleEditorWindows::DrawDirectoryRecursive(const char* directory, const char* filter_extension)
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
	
}
*/