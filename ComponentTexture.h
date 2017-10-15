#pragma once
#include "Globals.h"

#include "Component.h"
#include <vector>
#include "MathGeoLib-1.5\src\Math\float4.h"
struct Texture
{
	uint id;
	std::string type;
	std::string path;
	float4 rgba_color = { 1.0f,1.0f,1.0f,1.0f };

};
class ComponentTexture:public Component
{
public:
	ComponentTexture();
	~ComponentTexture();
	void Update();
	void GuiDraw();
	std::vector<Texture> textures;

};

