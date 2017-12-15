#include "UI_Inspector.h"
#include "GameObject.h"
#include "imgui/imgui.h"
#include "Resource.h"
#include "ModuleEditorWindows.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Component.h"
UI_Inspector::UI_Inspector(ModuleEditorWindows* my_editor) :UI_Windows(my_editor)
{

	names[MESH] = "Mesh";
	names[MESH_RENDER] = "Mesh Render";
	names[CAMERA] = "Camera";
	names[CANVAS] = "Canvas";
	names[CANVAS_IMAGE] = "Image";
	names[CANVAS_BUTTON] = "Button";
	names[CANVAS_TEXT] = "Text";
	names[CANVAS_CHECKBOX] = "CheckBox";
	names[CANVAS_INPUT_TEXT] = "Input Text";

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

	ImGui::SetNextWindowPos(ImVec2(SDL_GetWindowSurface(App->window->window)->w -350, 20), ImGuiCond_Always);

	ImGui::SetNextWindowSize(ImVec2(350, SDL_GetWindowSurface(App->window->window)->h-250), ImGuiCond_Always);
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
	case I_RESOURCE:
		InspectorResource();
		break;
	case I_NONE:
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
	selected_resource = nullptr;
	names.clear();
	show = I_NONE;

}

void UI_Inspector::SetSelectedGameObject(GameObject * set)
{
	selected_go = set;
	show = I_GO;
	selected_resource = nullptr;
}

void UI_Inspector::SetSelectedResource(Resource * set)
{
	selected_resource = set;
	show = I_RESOURCE;
	selected_go = nullptr;
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
		ComponentType selected_fish = NO_COMPONENT;
		if (ImGui::Button("Create Component.."))
			ImGui::OpenPopup("select");
		ImGui::SameLine();
		if (ImGui::BeginPopup("select"))
		{
			int i = 0;
			for (std::map<ComponentType, const char*>::const_iterator it = names.begin(); it != names.end(); it++)
			{
				if (ImGui::Selectable(it->second))
					selected_fish = it->first;
				i++;
			}
				
			ImGui::EndPopup();
		}
		if(selected_fish!= NO_COMPONENT)
		selected_go->CreateComponent(selected_fish);
	}
}

void UI_Inspector::InspectorResource()
{
	if (selected_resource != nullptr)
	{
		selected_resource->InspectorUpdate();
		if (ImGui::Button("Save##save_resource"))
		{
			selected_resource->ReImport();
			//save new resources values,
			//if resource is loaded, unload resource and load again
			//else do nothing
		}
	}
}
