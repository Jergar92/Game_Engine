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
class ComponentImage:public Component
{
public:
	ComponentImage(GameObject* my_go);
	~ComponentImage();
};

