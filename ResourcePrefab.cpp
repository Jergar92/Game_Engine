#include "ResourcePrefab.h"
#include "imgui/imgui.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleEditorWindows.h"
#include "ModuleScene.h"
ResourcePrefab::ResourcePrefab(uint UID) : Resource(UID, ResourceType::R_PREFAB)
{
}


ResourcePrefab::~ResourcePrefab()
{
}

void ResourcePrefab::LoadInMemory()
{
	JSONConfig config;

	if (!config.ParseFile(library_file.c_str(), App->file_system->GetMeshesFolder()))
		return;

	uint size = config.GetArraySize("GameObject");
	std::vector < GameObject*> tmp_go;
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = config.SetFocusArray("GameObject", i);
		GameObject* item = App->scene->GenerateGameObject();
		item->LoadGameObject(config_item);
		tmp_go.push_back(item);

	}
	for (int i = 0; i < tmp_go.size(); i++)
	{

		GameObject* item = tmp_go[i];
		if (item->GetParentUID() == 0)
		{
			item->SetParent(App->scene->GetScene());
		}
		else
		{
			item->SetParent(App->scene->FindGameObjectByID(tmp_go, item->GetParentUID()));
			item->GenerateBoudingBox();
		}
		item->UpdateMatrix();

	}
	for (int i = 0; i < tmp_go.size(); i++)
	{
		GameObject* item = tmp_go[i];
		item->ChangeUID();

	}
	config.CleanUp();
	App->editor_window->SetSceneGameObject(App->scene->GetScene());
}

void ResourcePrefab::InspectorUpdate()
{
	//Change name
	ImGui::Text("Resource Prefab: %s", original_file.c_str());
	ImGui::Text("UID: %i", UID);
}

void ResourcePrefab::SaveResource(JSONConfig & config) const
{
	config.SetInt(type, "Resource Type");
	config.SetInt(UID, "Resource UID");
	config.SetString(creation_time, "File Creation");

	config.SetString(original_file, "Original File");
	config.SetString(library_file, "Library File");
	config.SetString(meta_file, "Meta File");

}
void ResourcePrefab::LoadResource(const JSONConfig & config)
{
	creation_time = config.GetString("File Creation");

	original_file = config.GetString("Original File");
	library_file = config.GetString("Library File");
	meta_file = config.GetString("Meta File");

}
