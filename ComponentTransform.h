#pragma once
#include "Component.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\Quat.h"
class ComponentTransform:public Component
{
public:
	ComponentTransform(GameObject* my_go);
	~ComponentTransform();
	void SetTransform(float3 scale, Quat rotation, float3 position);
	void GuiDraw();
public:
	float3 scale;
	Quat rotation;
	float3 position;
};

