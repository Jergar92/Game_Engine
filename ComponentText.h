#pragma once
#include "Globals.h"
#include "Component.h"
class ResourceFont;
class ComponentText:public Component
{
public:
	ComponentText(GameObject* my_go);
	~ComponentText();
	void InspectorUpdate();
	ResourceFont* text=nullptr;
private:
	bool show_resource_font_windows = false;
	void SetString(std::string input);
	std::string text_str;
	std::string input_text;
	int max_input = 20;
};

