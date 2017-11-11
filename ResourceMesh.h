#pragma once
#include "Resource.h"

#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"

struct Vertex
{
	float3 position;
	float3 normals;
	float2 tex_coords;
};

class ResourceMesh :public Resource
{
public:
	ResourceMesh(uint UID);
	~ResourceMesh();
	void SetupMesh();
	void CleanUp();

	void DrawMesh(bool show);
	void LoadInMemory();
	//Getters
	const std::vector<Vertex>& GetVertices()const;
	const std::vector<uint>& GetIndices()const;
	const uint GetVertexBuffer()const;
	const uint GetElementBuffer()const;
	const uint GetVertexNormalID()const;
	const uint GetSurfaceNormalID()const;
	const bool GetDrawMesh()const;
	const bool GetDebugNormal()const;
	std::string GetMeshName()const;


	//Setters
	void SetData(const std::vector<Vertex> &vertices, const std::vector<uint> &indices, const int num_vertices, const int num_indices);
	void SetMeshName(std::string mesh_name);

	//Save&Load
	void SaveResource(JSONConfig& data)const;
	void LoadResource(const JSONConfig& data);

private:
	uint VBO = 0;//Vertex Buffer Object
	uint EBO = 0;//Element Buffer Object+
	uint vertex_normals_id = 0;//vertex_normals_id
	uint surface_normals_id = 0;//surface_normals_id
	std::string name;
	std::string mesh_name;

	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	uint num_vertices = 0;
	uint num_indices = 0;
	AABB bounding_box;
	bool debug_normals_succes = true;
	bool draw_mesh = true;
};

