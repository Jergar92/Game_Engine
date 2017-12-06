#pragma once
#include "Globals.h"
#include "Component.h"
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
	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

private:
	ImageRect image_rect;
	bool show_mesh_renderer_window = false;
	ResourceTexture* image=nullptr;

};

