#pragma once
#include "Resource.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
#include <string>

class ResourceTexture :public Resource
{
public:
	ResourceTexture(uint UID);
	~ResourceTexture();
	void SetID(uint id);
	uint GetUID()const;
	float4 GetRGBA()const;

private:
	uint id;
//	std::string name;
//	std::string type;
//	std::string path;
	float4 rgba_color;
};

