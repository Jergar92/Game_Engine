#include "Application.h"
#include "Globals.h"
#include"ModuleMenuBar.h"
#include"p2Defs.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleMenuBar::ModuleMenuBar(bool start_enabled)
{
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

update_status ModuleMenuBar::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleMenuBar::Update(float dt)
{
	ShowMenuBar();
	
	if (App->console->GetShowConsole())
		App->console->Draw("Console Ready");
	
	if (GetAboutUsStatus())
		AboutUsWindow();

	if (GetUpdateStatus())
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}


bool ModuleMenuBar::CleanUp()
{
	bool ret = true;
	return ret;
}


void ModuleMenuBar::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open"))
			{

			}

			if (ImGui::MenuItem("Save"))
			{

			
			}

			if (ImGui::MenuItem("Quit", "alt+f4"))
			{
				StopUpdate();
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
	
	
}

void ModuleMenuBar::AboutUs()
{
	show_about_us = !show_about_us;
}

void ModuleMenuBar::AboutUsWindow()
{
	ImGui::Begin("About Us", &open);
	open = !open;
	ImGui::Text("\n Name: Frog Engine. \n Description: this game engine is created for two student of the UPC, Enjoi It. . \n Creators: Andreu Rojas, and Sergio Saez. \n Licenses:  ");
	ImGui::End();
}

bool ModuleMenuBar::GetAboutUsStatus()
{
	return show_about_us;
}

bool ModuleMenuBar::GetUpdateStatus()
{
	return  stop_update;
}

void ModuleMenuBar::StopUpdate()
{
	stop_update = !stop_update;
}

void ModuleMenuBar::Console()
{
	App->console->ActiveConsole();
}

void ModuleMenuBar::Configuration()
{
	App->LoadConfigWindows();
}
