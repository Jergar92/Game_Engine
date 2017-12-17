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
	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);
	void InspectorUpdate();

	void Render();
	void CleanUp();
	void SetUpCanvasSize(SDL_Window* window);
	void SetUpRender();
	void ResetRender();
	void AddCanvasRender(ComponentCanvasRenderer* canvas_render);
	
	//interactive list functions
	void UpdateInteractiveMap();

	//Components Interactive Functions
	void UpdateFocus();
	void UpdateInput();
	void UpdateInteractive();
	void UpdateDrag();

	void WindowLimits();

	void EventString(const char* str);
	void FadeParent();

	//Draw Canvas function
	void DebugDraw();

	void EraseInteractiveElement(ComponentInteractive* element);

public:

	std::vector<ComponentInteractive*> interactive_array;
	std::multimap<float, ComponentInteractive*> interactive_z_map;
	std::multimap<float, ComponentInteractive*> interactive_x_map;

private:

	std::list<ComponentCanvasRenderer*> canvas_render;
	
	ComponentInteractive* current_focus = nullptr;
	CanvasData canvas_data;
	bool on_ejecution = false;
	GLint last_texture;
	GLint last_polygon_mode[2];
	GLint last_scissor_box[4];
	GLint last_viewport[4];

};

