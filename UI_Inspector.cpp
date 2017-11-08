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
	switch (show)
	{
	case I_GO:
		InspectorGameObject();
		break;
	case I_MESH:
		break;
	case I_TEXTURE:
		break;
	default:
		break;
	}
	ImGui::End();
	return true;
}

void UI_Inspector::CleanUp()
{
	selected_go = nullptr;
}

void UI_Inspector::SetSelectedGameObject(GameObject * set)
{
	selected_go = set;

}

GameObject * UI_Inspector::GetSelected() const
{
	return selected_go;
}

void UI_Inspector::InspectorGameObject()
{
	if (selected_go != nullptr)
	{
		selected_go->InspectorUpdate();


		int selected_fish = -1;
		/*
		Respect Order from ComponentType on Components.h
		*/
		const char* names[] = { "Mesh", "Mesh Renderer", "Camera" };

		// Simple selection popup
		// (If you want to show the current selection inside the Button itself, you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
		if (ImGui::Button("Create Component.."))
			ImGui::OpenPopup("select");
		ImGui::SameLine();
		if (ImGui::BeginPopup("select"))
		{
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
					selected_fish = i;
			ImGui::EndPopup();
		}
		if(selected_fish!=-1)
		selected_go->CreateComponent(static_cast<ComponentType>(selected_fish));
	}
}
