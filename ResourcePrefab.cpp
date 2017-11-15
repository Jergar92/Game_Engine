#include "ResourcePrefab.h"
#include "imgui/imgui.h"


ResourcePrefab::ResourcePrefab(uint UID) : Resource(UID, ResourceType::R_MESH)
{
}


ResourcePrefab::~ResourcePrefab()
{
}

void ResourcePrefab::LoadInMemory()
{
}

void ResourcePrefab::Load()
{
}

void ResourcePrefab::UnLoadInMemory()
{
}

void ResourcePrefab::UnLoad()
{
}

void ResourcePrefab::InspectorUpdate()
{
	//Change name
	ImGui::Text("Resource Prefab: %s", original_file.c_str());
	ImGui::Text("Load in memory: %i", load_count);
	ImGui::Text("UID: %i", UID);
}
