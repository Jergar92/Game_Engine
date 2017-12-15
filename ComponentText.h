#pragma once
#include "Globals.h"
#include "Component.h"
class ResourceFont;
struct GlyphData
{
	float3 positions[4];
	float2 text_cords[4];
	float offset_x, offset_y;
};
struct SDL_Surface;
class ComponentText:public Component
{
public:
	ComponentText(GameObject* my_go);
	~ComponentText();
	void InspectorUpdate();
	uint GetID();
	void UpdateText();
	SDL_Surface * s_font = nullptr;


	ResourceFont* text=nullptr;
	std::string text_str;
	float4 color;
	uint id = 0;//Vertex Buffer Object
private:
	bool show_resource_font_windows = false;
	void SetString(std::string input);
	std::string input_text;
	int max_input = 20;
};

