#pragma once
#include "Resource.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
#include <string>

class ResourceTexture :public Resource
{
public:
	ResourceTexture(uint UID);
	~ResourceTexture();

	uint GetID()const;
	float4 GetRGBA()const;
	void SetRGBA(float4 rgba);

	void SetID(uint id);
	void LoadInMemory();
	std::string path;
	std::string text_type;

private:
	uint id;
//	std::string name;
//	std::string path;
	float4 rgba_color;
};

