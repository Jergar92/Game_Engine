#include "UI_About.h"
#include "imgui/imgui.h"
#include "Globals.h"
#include "ModuleEditorWindows.h"

UI_About::UI_About(ModuleEditorWindows* my_editor):UI_Windows(my_editor)
{
	active_draw = false;
}


UI_About::~UI_About()
{
}

bool UI_About::Draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowSize(ImVec2(510, 300), ImGuiCond_Once);

	ImGui::Begin("About Us", &active_draw, window_flags);
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
		ShellExecute(NULL, "open", "https://github.com/nlohmann/json", NULL, NULL, SW_MINIMIZE);
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
	return true;
}
