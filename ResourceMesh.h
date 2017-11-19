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
	void Load();
	void UnLoadInMemory();
	void UnLoad();
	void InspectorUpdate();
	//Getters
	const std::vector<Vertex>& GetVertices()const;
	const std::vector<uint>& GetIndices()const;
	uint GetVertexBuffer()const;
	uint GetElementBuffer()const;
	uint GetNumVertices()const;
	uint GetNumIndices()const;
	bool GetDrawMesh()const;


	//Setters
	void SetData(const std::vector<Vertex> &vertices, const std::vector<uint> &indices, int num_vertices, int num_indices);

	//Save&Load
	void ReImport();
	void SaveResource(JSONConfig& data)const;
	void LoadResource(const JSONConfig& data);

private:
	uint VBO = 0;//Vertex Buffer Object
	uint EBO = 0;//Element Buffer Object+
	std::string name;

	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	uint num_vertices = 0;
	uint num_indices = 0;
	bool draw_mesh = true;
};

