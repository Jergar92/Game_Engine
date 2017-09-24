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

	if (App->console->GetShowConsole())
		App->console->Draw("Console Ready");
	
	if (GetAboutUsStatus())
		AboutUsWindow();

	if (Draw(open))
	{
		ShowMenuBar();
	}
	else
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

			ImGui::Separator();

			if (ImGui::MenuItem("Save"))
			{

			
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Save as"))
			{


			}

			ImGui::Separator();

			if (ImGui::MenuItem("Load"))
			{


			}

			ImGui::Separator();

			if (ImGui::MenuItem("Quit", "alt+f4"))
			{
				open = false;
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
	ImGui::Begin("About Us", &show_about_us);
	ImGui::Text("\n Name: Frog Engine. \n Description: this game engine is created for two student of the UPC, Enjoi It. \n Creators: \n Andreu Rojas  \n Sergio Saez. \n Licenses: \n mathgeolib v1.5 \n sdl v2.0.3 \n imgui v.152 WIP \n JSON library writen in C ");
	ImGui::End();
}

bool ModuleMenuBar::GetAboutUsStatus()
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
