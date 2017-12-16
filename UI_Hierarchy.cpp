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
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Game Object");
			App->scene->SendGameObject(main_go);	
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Generate Canvas"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::Button("Generate Image"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* image = App->scene->GenerateGameObject();
			main_go->SetName("Image");
			image->SetParent(main_go);
			main_go->CreateComponent(ComponentType::CANVAS_IMAGE);


			App->scene->SendGameObject(main_go);
			App->scene->SendGameObject(image);

			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Generate Panel"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* image = App->scene->GenerateGameObject();
			main_go->SetName("Image");
			image->SetParent(main_go);
			main_go->CreateComponent(ComponentType::CANVAS_IMAGE);
			main_go->CreateComponent(ComponentType::CANVAS_IMDRAG);

			App->scene->SendGameObject(main_go);
			App->scene->SendGameObject(image);



		}
		if (ImGui::Button("Generate Button"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* image = App->scene->GenerateGameObject();
			main_go->SetName("Image");
			image->SetParent(main_go);
			main_go->CreateComponent(ComponentType::CANVAS_IMAGE);
			main_go->CreateComponent(ComponentType::CANVAS_BUTTON);


			App->scene->SendGameObject(main_go);
			App->scene->SendGameObject(image);
		}
		if (ImGui::Button("Generate CheckBox"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* image = App->scene->GenerateGameObject();
			main_go->SetName("Image");
			image->SetParent(main_go);
			main_go->CreateComponent(ComponentType::CANVAS_IMAGE);
			main_go->CreateComponent(ComponentType::CANVAS_CHECKBOX);


			App->scene->SendGameObject(main_go);
			App->scene->SendGameObject(image);
		}
		if (ImGui::Button("Generate Texto"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* text = App->scene->GenerateGameObject();
			main_go->SetName("Image");
			text->SetParent(main_go);
			main_go->CreateComponent(ComponentType::CANVAS_TEXT);


			App->scene->SendGameObject(main_go);
			App->scene->SendGameObject(text);
		}
		if (ImGui::Button("Generate InputText"))
		{
			GameObject* main_go = App->scene->GenerateGameObject();
			main_go->SetName("Canvas");
			App->scene->SendGameObject(main_go);
			main_go->CreateComponent(ComponentType::CANVAS);

			GameObject* text = App->scene->GenerateGameObject();
			main_go->SetName("Image");
			text->SetParent(main_go);
			main_go->CreateComponent(ComponentType::CANVAS_TEXT);
			main_go->CreateComponent(ComponentType::CANVAS_INPUT_TEXT);


			App->scene->SendGameObject(main_go);
			App->scene->SendGameObject(text);
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
