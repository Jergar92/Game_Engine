#pragma once
#include "Globals.h"
#include <list>

#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "Component.h"


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

	std::list<ComponentCanvasRenderer*> canvas_render;
	CanvasData canvas_data;

	GLint last_texture;
	GLint last_polygon_mode[2];
	GLint last_scissor_box[4];
	GLint last_viewport[4];

};

