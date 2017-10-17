#pragma once
#include "Component.h"

#include "Globals.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
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

	void SetupMesh();
	void GuiUpdate();
	void InspectorUpdate();

	void SetData(const std::vector<Vertex> &vertices, const std::vector<uint> &indices);
	const std::vector<Vertex>& GetVertices();
	const std::vector<uint>& GetIndices();
	const uint GetVertexBuffer();
	const uint GetElementBuffer();
	void Update();
public:
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
};

