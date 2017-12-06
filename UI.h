#pragma once
#include "Globals.h"
#include <map>
#include <vector>

#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
struct CanvasVertex;

struct CanvasBuffer
{
	CanvasBuffer();
	std::vector<CanvasVertex> vertices;
	std::vector<uint> indices;

	uint VBO=0;
	uint EBO=0;

	uint texture_id = 0;
};

struct CanvasVertex
{
	float3 position;
	//float3 normals;
	float2 tex_coords;
};
class ComponentCanvasRenderer;
class UI
{
public:
	UI();
	~UI();
	void Render();
	void SetUpCanvas();
	void AddCanvasRender(ComponentCanvasRenderer* canvas_render);
private:
	std::map<uint, CanvasBuffer*> canvas_buffer;


};

extern UI* Canvas;