#pragma once
#include "Globals.h"
#include "Component.h"
class ResourceFont;
struct TextureRect
{
	float x=0;
	float y=0;
	float width=0;
	float height=0;

};
struct SDL_Surface;
class ComponentText:public Component
{
public:
	ComponentText(GameObject* my_go);
	~ComponentText();
	void InspectorUpdate();
	void CleanUp();
	uint GetID();
	void FreeFont();
	void UpdateText();
	SDL_Surface * s_font = nullptr;
	const TextureRect GetRect() const;
	void SetUpdateText(bool value);
	int GetMaxInput()const;
	bool GetUpdateText() const;
	void SetRect(float x, float y, float width, float height);
	ResourceFont* text=nullptr;
	std::string text_str;
	uint id = 0;//Vertex Buffer Object
private:
	bool update_text = false;
	TextureRect text_rect;
	float4 color = float4::one;
	bool show_resource_font_windows = false;
	void SetString(std::string input);
	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);
	std::string input_text;
	int max_input = 20;

};

