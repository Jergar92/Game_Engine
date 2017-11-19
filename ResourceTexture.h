#pragma once
#include "Resource.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
#include <string>

class ResourceTexture :public Resource
{
public:
	ResourceTexture(uint UID);
	~ResourceTexture();
	void LoadInMemory();
	void Load();
	void UnLoadInMemory();
	void UnLoad();
	void ReImport();
	void InspectorUpdate();
	void CleanUp();

	void SetRGBA(float4 rgba);
	void SetID(uint id);

	uint GetID()const;
	float4 GetRGBA()const;
	bool GetFlip()const;

	void SaveResource(JSONConfig& config)const;
	void LoadResource(const JSONConfig& config);

public:
	std::string path;
private:
	uint id=-1;
	float4 rgba_color=float4::one;
	bool flip = true;
};

