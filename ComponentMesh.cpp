#include "ComponentMesh.h"
#include "Application.h"
#include "GameObject.h"
#include "ResourceMesh.h"
#include "ModuleResourceManager.h"

#include "Glew\include\GL\glew.h"
#include "imgui\imgui.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"

ComponentMesh::ComponentMesh(GameObject* my_go) :Component(my_go),r_mesh(nullptr)
{
	component_name = "Mesh";
	type = MESH;
}


ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::InspectorUpdate()
{

	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);
	if (ImGui::BeginPopupContextItem("go_options"))
	{	//Scene GO protection

		if (ImGui::Button("Delete Component"))
		{
			DeleteComponent();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	if (node_open)
	{
		int num_vertices = (r_mesh == nullptr) ? 0 : r_mesh->GetNumVertices();
		int num_indices = (r_mesh == nullptr) ? 0 : r_mesh->GetNumIndices();

		ImGui::Text("Vertices:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", num_vertices);

		ImGui::Text("Indices:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", num_indices);

		if (ImGui::Button("Select Mesh"))
		{
			show_mesh_window = true;
		}
		ImGui::TreePop();
	}
	if (show_mesh_window)
	{
		uint UID=App->resource_manager->ResourceWindows(R_MESH);
		if (UID == -1)
		{
			show_mesh_window = false;
		}
		else if (UID != 0)
		{		
			Resource* new_resource = App->resource_manager->Get(UID);
			bool update = true;
			if (r_mesh != nullptr)
			{
				if (new_resource->GetOriginalFile().compare(r_mesh->GetOriginalFile()) == 0)
				{
					update = false;
				}
				else
				{
					r_mesh->UnLoadInMemory();
				}
			}
			if (update)
			{
				r_mesh = (ResourceMesh*)new_resource;
				r_mesh->LoadInMemory();
			}
			show_mesh_window = false;
			ImGui::CloseCurrentPopup();			
		}
	}
}
	

void ComponentMesh::CleanUp()
{
	if (r_mesh != nullptr)
	{
		r_mesh->UnLoadInMemory();
		r_mesh = nullptr;
	}
}
void ComponentMesh::SetResourceMesh(ResourceMesh* mesh)
{
	r_mesh = mesh;
	my_go->GenerateBoudingBox();
}

const std::vector<Vertex>& ComponentMesh::GetVertices()const
{
	return r_mesh->GetVertices();
}
const std::vector<uint>& ComponentMesh::GetIndices()const
{
	return r_mesh->GetIndices();
}
uint ComponentMesh::GetVertexBuffer()const
{
	return r_mesh->GetVertexBuffer();
}
uint ComponentMesh::GetElementBuffer()const
{
	return r_mesh->GetElementBuffer();
}
uint ComponentMesh::GetVertexNormalID() const
{
	return r_mesh->GetVertexNormalID();
}
uint ComponentMesh::GetSurfaceNormalID() const
{
	return r_mesh->GetSurfaceNormalID();
}
const ResourceMesh * ComponentMesh::GetResourceMesh() const
{
	return r_mesh;
}
bool ComponentMesh::HaveResourceMesh() const
{
	if (r_mesh == nullptr)
		return false;
	return true;
}
bool ComponentMesh::GetDrawMesh() const
{
	return draw_mesh;
}

void ComponentMesh::DrawMesh(bool show)
{
	draw_mesh = show;
}

bool ComponentMesh::GetDebugNormal() const
{
	return debug_normals_succes;
}




void ComponentMesh::Update()
{

}

bool ComponentMesh::SaveComponent(JSONConfig & config) const
{
	bool ret = true;
	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");

	if (r_mesh != nullptr)
	{
	config.SetInt(r_mesh->GetResourceType(),"ResourceType");
	config.SetInt(r_mesh->GetUID(), "Resource UID");
	}
	
	config.SetBool(enable, "Enable");

	//save the path of the mesh.frog
	return ret;
}

bool ComponentMesh::LoadComponent(const JSONConfig & config)
{
	bool ret = true;

	
	if(config.GetInt("ResourceType")!=0)
	{
		r_mesh = (ResourceMesh*)App->resource_manager->Get(config.GetInt("Resource UID"));
		if (r_mesh != nullptr)
		{
			r_mesh->LoadInMemory();
			my_go->GenerateBoudingBox();
		}
	}
	
	enable= config.GetBool( "Enable");

	return ret;
}