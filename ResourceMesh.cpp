#include "ResourceMesh.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "Glew\include\GL\glew.h"
#include "imgui\imgui.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"
#include "GameObject.h"


ResourceMesh::ResourceMesh(uint UID) :Resource(UID, ResourceType::R_MESH)
{
}


ResourceMesh::~ResourceMesh()
{
}

void ResourceMesh::SetupMesh()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	if (indices.size() != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
		//set bind buffer glBindBuffer to 0
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}	
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ResourceMesh::CleanUp()
{
	vertices.clear();
	indices.clear();
}
void ResourceMesh::SetData(const std::vector<Vertex>& set_vertices, const std::vector<uint>& set_indices, const int num_ver, const int num_ind)
{
	vertices = set_vertices;
	indices = set_indices;
	num_vertices = num_ver;
	num_indices = num_ind;
}
void ResourceMesh::SetMeshName(std::string set_mesh_name)
{
	mesh_name = set_mesh_name;
}
void ResourceMesh::ReImport()
{
	JSONConfig config;
	config.ParseFile(meta_file.c_str());
	SaveResource(config);
	if (!IsLoadInMemory())
	{
		UnLoadInMemory();
		LoadInMemory();
	}
}
void ResourceMesh::SaveResource(JSONConfig & config) const
{
	config.SetInt(type, "Resource Type");
	config.SetInt(UID, "Resource UID");

	config.SetString(original_file, "Original File");
	config.SetString(library_file, "Library File");
	config.SetString(meta_file, "Meta File");

}
void ResourceMesh::LoadResource(const JSONConfig & config)
{
	original_file = config.GetString("Original File");
	library_file = config.GetString("Library File");
	meta_file = config.GetString("Meta File");
	
}
const std::vector<Vertex>& ResourceMesh::GetVertices()const
{
	return vertices;
}
const std::vector<uint>& ResourceMesh::GetIndices()const
{
	return indices;
}
uint ResourceMesh::GetVertexBuffer()const
{
	return VBO;
}
uint ResourceMesh::GetElementBuffer()const
{
	return EBO;
}
uint ResourceMesh::GetVertexNormalID() const
{
	return vertex_normals_id;
}
uint ResourceMesh::GetSurfaceNormalID() const
{
	return surface_normals_id;
}
uint ResourceMesh::GetNumVertices() const
{
	return num_vertices;
}
uint ResourceMesh::GetNumIndices() const
{
	return num_indices;
}
bool ResourceMesh::GetDrawMesh() const
{
	return draw_mesh;
}
bool ResourceMesh::GetDebugNormal() const
{
	return debug_normals_succes;
}

const std::string ResourceMesh::GetMeshName() const
{
	return mesh_name;
}

void ResourceMesh::DrawMesh(bool show)
{
	draw_mesh = show;
}

void ResourceMesh::LoadInMemory()
{
	if (IsLoadInMemory())
	{
		Load();
	}
	load_count++;
}

void ResourceMesh::Load()
{
	App->importer->LoadMesh(this);

}

void ResourceMesh::UnLoadInMemory()
{
	load_count--;
	if (IsLoadInMemory())
	{
		UnLoad();
	}
}

void ResourceMesh::UnLoad()
{
	vertices.clear();
	indices.clear();
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void ResourceMesh::InspectorUpdate()
{
	
	//Change name
	ImGui::Text("ResourceMesh: %s", original_file.c_str());
	ImGui::Text("Load in memory: %i",load_count);
	ImGui::Text("UID: %i", UID);

}




