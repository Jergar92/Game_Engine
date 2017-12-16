#pragma once
#include "Globals.h"
#include "ComponentInteractive.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

class ResourceTexture;

class ComponentPanel :public ComponentInteractive
{
public:
	ComponentPanel(GameObject* my_go);
	~ComponentPanel();
	void Update(float dt);

	void InspectorUpdate();
	const ResourceTexture* GetImage()const;
	void EqualizeUv();
	void EqualizeWorldUv();
	void SetWorldUvValues();
	uint GetImageID()const;

	float2 GetUV0()const;
	float2 GetUV1()const;

	void Idle();
	void Hover();
	void Down();

	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

	ResourceTexture* image = nullptr;

	void ChangeImage(uint ID);
private:
	float2 world_uv0 = float2::zero;
	float2 world_uv1 = float2::one;
	float2 uv0 = float2::zero;
	float2 uv1 = float2::one;

	uint tmp_id = 0;

	bool show_mesh_renderer_window = false;


};