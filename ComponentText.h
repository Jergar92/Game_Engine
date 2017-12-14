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
class ComponentText:public Component
{
public:
	ComponentText(GameObject* my_go);
	~ComponentText();
	void InspectorUpdate();
	GlyphData getGlyphInfo(uint character, float offset_x, float offset_y);
	uint GetID();
	ResourceFont* text=nullptr;
	std::string text_str;

	uint VBO = 0;//Vertex Buffer Object
	uint EBO = 0;//Element Buffer Object+
private:
	bool show_resource_font_windows = false;
	void SetString(std::string input);
	std::string input_text;
	int max_input = 20;
};

