#include "UI_Play.h"
#include "imgui/imgui.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditorWindows.h"
#include "ModuleFileSystem.h"
UI_Play::UI_Play()
{
}


UI_Play::~UI_Play()
{
}

bool UI_Play::Draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoMove;

	ImGui::SetNextWindowPos(ImVec2(SDL_GetWindowSurface(App->window->window)->w *0.5, 20), ImGuiCond_Always);

	ImGui::SetNextWindowSize(ImVec2(150, 50), ImGuiCond_Once);

	if (!ImGui::Begin("Editor Play", &active_draw, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return true;
	}
	if(ImGui::Button("Play"))
	{
		App->editor_window->WantToSave("play.json", App->file_system->GetPlayFolder());
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause"))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		App->editor_window->WantToLoad("play.json", App->file_system->GetPlayFolder());

	}

	ImGui::End();

	return true;
}
