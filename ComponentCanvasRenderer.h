#pragma once
#include "Globals.h"
#include "Component.h"
#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

class ComponentImage;
class Component;
class ComponentCanvas;
class ComponentCanvasRenderer :public Component
{
public:
	ComponentCanvasRenderer(GameObject* my_go);
	~ComponentCanvasRenderer();

	void Update(float dt);
	void CleanUp();
	void GetComponent(Component* item);
	void ProcessImage();
	void SetUpCanvas();
	ComponentCanvas* FindMyCanvas();
	ComponentImage* image;

private:
	ComponentCanvas* canvas = nullptr;

};

