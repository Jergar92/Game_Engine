#include "UI_Hierarchy.h"
#include "GameObject.h"
#include "imgui/imgui.h"

UI_Hierarchy::UI_Hierarchy()
{
}


UI_Hierarchy::~UI_Hierarchy()
{
	scene_go = nullptr;
}

bool UI_Hierarchy::Draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_Once);
	if (!ImGui::Begin("Hierarchy", &active_draw, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
	}
	if (scene_go != nullptr)
	{
		scene_go->GuiUpdate();
	}
	ImGui::End();
	return true;
}

void UI_Hierarchy::SetSceneGameObject(GameObject * set)
{
	scene_go = set;
}
