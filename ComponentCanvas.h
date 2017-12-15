#pragma once
#include "Globals.h"
#include <list>
#include <vector>
#include <map>

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
class ComponentImage;
class ComponentInteractive;
struct SDL_Window;
typedef int GLint;

class ComponentCanvas:public Component
{
public:
	ComponentCanvas(GameObject* my_go);
	~ComponentCanvas();
	void OnPlay();
	void Update(float dt);
	void OnStop();
	void Render();
	void SetUpCanvasSize(SDL_Window* window);
	void SetUpRender();
	void ResetRender();
	void AddCanvasRender(ComponentCanvasRenderer* canvas_render);
	void UpdateInteractive();
	void UpdateInteractiveMap();
	void DebugDraw();

public:

	std::vector<ComponentInteractive*> interactive_array;
	std::multimap<float, ComponentInteractive*> interactive_z_map;

private:

	std::list<ComponentCanvasRenderer*> canvas_render;
	

	CanvasData canvas_data;
	bool on_ejecution = false;
	GLint last_texture;
	GLint last_polygon_mode[2];
	GLint last_scissor_box[4];
	GLint last_viewport[4];

};

