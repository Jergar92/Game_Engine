#pragma once
#include "Globals.h"
#include <map>
#include <vector>

#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "Component.h"
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
struct CanvasData
{
	//w = x...h=y
	float2 size=float2::one;
	float2 draw_size = float2::one;

};
class ComponentCanvasRenderer;
struct SDL_Window;
typedef int GLint;

class ComponentCanvas:public Component
{
public:
	ComponentCanvas(GameObject* my_go);
	~ComponentCanvas();
	void Update(float dt);
	void Render();
	void SetUpCanvasSize(SDL_Window* window);
	void SetUpCanvas();
	void SetUpRender();
	void ResetRender();
	void AddCanvasRender(ComponentCanvasRenderer* canvas_render);
private:
	std::map<uint, CanvasBuffer*> canvas_buffer;
	CanvasData canvas_data;

	GLint last_texture;
	GLint last_polygon_mode[2];
	GLint last_scissor_box[4];
	GLint last_viewport[4];

};

