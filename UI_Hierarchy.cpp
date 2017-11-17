#include "UI_Hierarchy.h"
#include "GameObject.h"
#include "imgui/imgui.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Application.h"
#include "ModuleWindow.h"
UI_Hierarchy::UI_Hierarchy(ModuleEditorWindows* my_editor) :UI_Windows(my_editor)
{
}


UI_Hierarchy::~UI_Hierarchy()
{
}

bool UI_Hierarchy::Draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);

	ImGui::SetNextWindowSize(ImVec2(350, SDL_GetWindowSurface(App->window->window)->h - 250), ImGuiCond_Always);

	ImGui::Begin("Hierarchy", &active_draw, window_flags);

	if (scene_go != nullptr)
	{
		scene_go->GuiUpdate();
	}

	ImGui::BeginChild("EndInspector Zone", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false);

	if (ImGui::BeginPopupContextWindow("go_options"))
	{

		if (ImGui::Button("Generate Game Object"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Game Object");
			App->scene->SendGameObject(main_go);	
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	ImGui::EndChild();

	ImGui::End();
	return true;
}

void UI_Hierarchy::CleanUp()
{
	scene_go = nullptr;

}

void UI_Hierarchy::SetSceneGameObject(GameObject * set)
{
	scene_go = set;
}
