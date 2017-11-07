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

	ImGui::SetNextWindowSize(ImVec2(250, 50), ImGuiCond_Once);

	if (!ImGui::Begin("Editor Play", &active_draw, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return true;
	}
	if(ImGui::Button("Play") &&( state == ON_NONE || state == ON_PAUSE))
	{

		App->editor_window->WantToSave("play.json", App->file_system->GetPlayFolder());
		state = ON_PLAY;
		App->OnPlay();

	}
	ImGui::SameLine();
	if (ImGui::Button("Pause")&&state==ON_PLAY)
	{
		state = ON_PAUSE;
		App->OnPause();

	}
	ImGui::SameLine();
	if (ImGui::Button("Stop")&& (state == ON_PLAY || state == ON_PAUSE))
	{
		App->editor_window->WantToLoad("play.json", App->file_system->GetPlayFolder());
		state = ON_NONE;
		value = 1.0f;
		App->OnStop();

	}
	if (state == ON_PLAY || state == ON_PAUSE)
	{
		ImGui::PushItemWidth(130);
		if (ImGui::DragFloat("", &value, 0.01f, 0.0f, 1.0f, "%0.2f", 1.0f))
			App->SetGameTimeMultiply(value);
		ImGui::PopItemWidth();
	}

	ImGui::End();

	return true;
}
