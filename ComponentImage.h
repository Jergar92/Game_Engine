#pragma once
#include "Globals.h"
#include "Component.h"
struct Quad
{
	Quad(int pos_x, int pos_y, int width, int height);
	int pos_x = 0;
	int pos_y = 0;
	int width = 100;
	int height = 100;
	float vertices[12] = { 0,0,0,0,0,0,0,0,0,0,0,0};
	float indices[6] = { 0,1,2,2,3,0};
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


	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

private:
	bool show_mesh_renderer_window = false;
	ResourceTexture* image=nullptr;

};

