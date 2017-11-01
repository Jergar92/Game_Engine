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
	void GenerateBoudingBox();

	//Getters
	const std::vector<Vertex>& GetVertices()const;
	const std::vector<uint>& GetIndices()const;
	const uint GetVertexBuffer()const;
	const uint GetElementBuffer()const;
	AABB GetBoundingBox() const;
	int GetUID()const;

	//Setters
	void SetData(const std::vector<Vertex> &vertices, const std::vector<uint> &indices, const int num_vertices, const int num_indices);
	void SetAABB(const AABB set_bounding_box);

	//Save&Load
	bool SaveComponent(JSONConfig& data)const;
	bool LoadComponent(const JSONConfig& data);

private:
	void RenderBoundingBox();

private:
	uint UID;// ID mesh
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

