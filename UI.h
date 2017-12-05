#pragma once
#include "Globals.h"
#include <vector>

#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

struct Vertex
{
	float3 position;
	float3 normals;
	float2 tex_coords;
};
class UI
{
public:
	UI();
	~UI();
	void Render();
	void SetUpCanvas();
	void AddCanvasRender();
private:
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	uint VBO;
	uint EBO;
};

