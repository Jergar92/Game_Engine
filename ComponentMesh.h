#pragma once
#include "Component.h"

#include "Globals.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"

struct Vertex
{
	float3 position;
	float3 normals;
	float2 tex_coords;
};

class ComponentMesh :public Component
{
public:
	ComponentMesh(GameObject* my_go);
	~ComponentMesh();
	void Update();
	void SetupMesh();
	void InspectorUpdate();

	void SetData(const std::vector<Vertex> &vertices, const std::vector<uint> &indices, const int num_vertices,const int num_indices);
	const std::vector<Vertex>& GetVertices();
	const std::vector<uint>& GetIndices();
	const uint GetVertexBuffer();
	const uint GetElementBuffer();
	void GenerateBoudingBox();
	void SetAABB(const AABB set_bounding_box);

private:
	void RenderBoundingBox();

private:
	uint VBO=0;//Vertex Buffer Object
	uint EBO=0;//Element Buffer Object
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	uint num_vertices=0;
	uint num_indices=0;
	AABB bounding_box;
	bool show_bounding_box=false;
};

