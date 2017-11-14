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
	bool GetFlip()const;
	void SetRGBA(float4 rgba);
	void SetID(uint id);
	void LoadInMemory();
	void UnLoadInMemory();
	void InspectorUpdate();
	std::string path;
	std::string text_type;
	std::string name;
	void SaveResource(JSONConfig& config)const;
	void LoadResource(const JSONConfig& config);
private:
	uint id=-1;
//	std::string path;
	float4 rgba_color=float4::one;
	bool flip = false;
};

