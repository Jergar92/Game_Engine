#pragma once
#include "Resource.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
#include <string>
struct Texture
{
	uint id;
	std::string name;
	std::string type;
	std::string path;
	float4 rgba_color;

};
class ResourceTexture :public Resource
{
public:
	ResourceTexture();
	~ResourceTexture();
};

