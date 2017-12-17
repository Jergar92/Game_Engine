#include "UI_Hierarchy.h"
#include "GameObject.h"
#include "imgui/imgui.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Application.h"
#include "Component.h"
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
	window_flags |= ImGuiWindowFlags_HorizontalScrollbar;

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
			GameObject* main_go = App->scene->GenerateGameObject(GO_ELEMENT);
			main_go->SetName("Game Object");
			App->scene->SendGameObject(main_go);	
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Generate Canvas"))
		{
			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
				main_go->SetName("Canvas");
				main_go->CreateComponent(ComponentType::CANVAS);
			}
		
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::Button("Generate Image"))
		{
			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
			}
			main_go->SetName("Canvas");
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* image = App->scene->GenerateGameObject(GO_CANVAS);
			image->SetName("Image");
			image->SetParent(main_go);
			image->CreateComponent(ComponentType::CANVAS_IMAGE);



			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Generate Panel"))
		{

			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
			}
			main_go->SetName("Canvas");
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* panel = App->scene->GenerateGameObject(GO_CANVAS);
			panel->SetName("Panel");
			panel->SetParent(main_go);
			panel->CreateComponent(ComponentType::CANVAS_IMAGE);
			panel->CreateComponent(ComponentType::CANVAS_IMDRAG);

			


		}
		if (ImGui::Button("Generate Button"))
		{

			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
			}
			main_go->SetName("Canvas");
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* button = App->scene->GenerateGameObject(GO_CANVAS);
			button->SetName("Button");
			button->SetParent(main_go);
			button->CreateComponent(ComponentType::CANVAS_IMAGE);
			button->CreateComponent(ComponentType::CANVAS_BUTTON);


		}
		if (ImGui::Button("Generate CheckBox"))
		{

			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
			}
			main_go->SetName("Canvas");
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* check_box = App->scene->GenerateGameObject(GO_CANVAS);
			check_box->SetName("Check Box");
			check_box->SetParent(main_go);
			check_box->CreateComponent(ComponentType::CANVAS_IMAGE);
			check_box->CreateComponent(ComponentType::CANVAS_CHECKBOX);


		}
		if (ImGui::Button("Generate Texto"))
		{

			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
			}
			main_go->SetName("Canvas");
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* text = App->scene->GenerateGameObject(GO_CANVAS);
			text->SetName("Text");
			text->SetParent(main_go);
			text->CreateComponent(ComponentType::CANVAS_TEXT);


		}
		if (ImGui::Button("Generate InputText"))
		{

			GameObject* main_go = App->scene->FindGameObjectComponent(ComponentType::CANVAS);
			if (main_go == nullptr)
			{
				main_go = App->scene->GenerateGameObject(GO_CANVAS);
				App->scene->SendGameObject(main_go);
			}
			main_go->SetName("Canvas");
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* text = App->scene->GenerateGameObject(GO_CANVAS);
			text->SetName("Input Text");
			text->SetParent(main_go);
			text->CreateComponent(ComponentType::CANVAS_TEXT);
			text->CreateComponent(ComponentType::CANVAS_INPUT_TEXT);


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
