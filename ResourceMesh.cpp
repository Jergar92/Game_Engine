#include "ResourceMesh.h"
#include "Application.h"

#include "Glew\include\GL\glew.h"
#include "imgui\imgui.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"
#include "GameObject.h"


ResourceMesh::ResourceMesh()
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
	if (indices.size() % 3 != 0)
	{
		LOG("ERROR is Not multiple of 3!");
		debug_normals_succes = false;
	}
	else {
		glGenBuffers(1, &vertex_normals_id);
		glGenBuffers(1, &surface_normals_id);

		std::vector<float3> vertex_normals;
		std::vector<float3> surface_normals;
		//vertex normal loop
		for (uint i = 0; i < indices.size(); i++)
		{
			int indice_number = indices[i];
			vertex_normals.push_back(vertices[indice_number].position);
			vertex_normals.push_back(vertices[indice_number].position + vertices[indice_number].normals);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_id);
		glBufferData(GL_ARRAY_BUFFER, vertex_normals.size() * sizeof(float3), &vertex_normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//surface normal loop
		for (uint i = 0; i < indices.size(); i += 3)
		{
			float3 vertexA = vertices[indices[i]].position;
			float3 vertexB = vertices[indices[i + 1]].position;
			float3 vertexC = vertices[indices[i + 2]].position;

			float3 edge1 = vertexB - vertexA;
			float3 edge2 = vertexC - vertexA;
			float3 surface_normal = Cross(edge1, edge2);
			surface_normal.Normalize();


			float3 center_point(
				((vertexA.x + vertexB.x + vertexC.x) / 3),
				((vertexA.y + vertexB.y + vertexC.y) / 3),
				((vertexA.z + vertexB.z + vertexC.z) / 3));

			surface_normals.push_back(center_point);
			surface_normals.push_back(center_point + surface_normal);
		}

		glBindBuffer(GL_ARRAY_BUFFER, surface_normals_id);
		glBufferData(GL_ARRAY_BUFFER, surface_normals.size() * sizeof(float3), &surface_normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

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
	SetupMesh();
}
void ResourceMesh::SetMeshName(std::string set_mesh_name)
{
	mesh_name = set_mesh_name;
}
const std::vector<Vertex>& ResourceMesh::GetVertices()const
{
	return vertices;
}
const std::vector<uint>& ResourceMesh::GetIndices()const
{
	return indices;
}
const uint ResourceMesh::GetVertexBuffer()const
{
	return VBO;
}
const uint ResourceMesh::GetElementBuffer()const
{
	return EBO;
}
const uint ResourceMesh::GetVertexNormalID() const
{
	return vertex_normals_id;
}
const uint ResourceMesh::GetSurfaceNormalID() const
{
	return surface_normals_id;
}
const bool ResourceMesh::GetDrawMesh() const
{
	return draw_mesh;
}

void ResourceMesh::DrawMesh(bool show)
{
	draw_mesh = show;
}

const bool ResourceMesh::GetDebugNormal() const
{
	return debug_normals_succes;
}

std::string ResourceMesh::GetMeshName() const
{
	return mesh_name;
}



