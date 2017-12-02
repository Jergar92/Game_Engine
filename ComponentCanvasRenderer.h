#pragma once
#include "Globals.h"
#include "Component.h"

class ComponentCanvasRenderer :public Component
{
public:
	ComponentCanvasRenderer(GameObject* my_go);
	~ComponentCanvasRenderer();

	void Update(float dt);

	void Draw();
	void InspectorUpdate();
	void CleanUp();
};

