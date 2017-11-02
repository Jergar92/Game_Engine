#include "UI_Inspector.h"
#include "GameObject.h"
#include "imgui/imgui.h"


UI_Inspector::UI_Inspector()
{
}


UI_Inspector::~UI_Inspector()
{
}

bool UI_Inspector::Draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_Once);
	if (!ImGui::Begin("Inspector", &active_draw, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
	}
	if (selected_go != nullptr)
	{
		selected_go->InspectorUpdate();
	}
	ImGui::End();
	return true;
}

void UI_Inspector::SetSelectedGameObject(GameObject * set)
{
}
