#pragma once
#include "Globals.h"
#include "Component.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

//TODO change for rectTransform
struct ImageRect
{
	ImageRect(int pos_x = 0, int pos_y =0, int width=10, int height= 10);
	int pos_x = 0;
	int pos_y = 0;
	int width = 100;
	int height = 100;
	float vertices[12] = { 0,0,0,0,0,0,0,0,0,0,0,0};

	void SetUpVertices();

};
class ResourceTexture;
class ComponentImage:public Component
{
public:
	ComponentImage(GameObject* my_go);
	~ComponentImage();
	void Update(float dt);

	void InspectorUpdate();
	const ImageRect GetImageRect()const;
	const ResourceTexture* GetImage()const;

	uint GetImageID()const;

	float2 GetUV0()const;
	float2 GetUV1()const;

	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

	//void Set_uv(float2 uv0, float2 uv1);
	ResourceTexture* image = nullptr;
private:
	float2 uv0 = float2::zero;
	float2 uv1 = float2::one;
	ImageRect image_rect;
	bool show_mesh_renderer_window = false;
	//ResourceTexture* image=nullptr;

};

