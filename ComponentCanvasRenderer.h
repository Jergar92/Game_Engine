#pragma once
#include "Globals.h"
#include "Component.h"
class ComponentImage;
class Component;
class ComponentCanvasRenderer :public Component
{
public:
	ComponentCanvasRenderer(GameObject* my_go);
	~ComponentCanvasRenderer();

	void Update(float dt);

	void Draw();

	void CleanUp();
	void GetComponent(Component* item);
	ComponentImage* image;
};

