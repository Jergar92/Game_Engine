#pragma once
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\Quat.h"

class ComponentTransform :public Component
{
public:
	ComponentTransform(GameObject* my_go);
	~ComponentTransform();
	void SetTransform(float3 scale, Quat rotation, float3 position);
	void GuiUpdate();
	void InspectorUpdate();

public:
	float3 scale;
	Quat rotation;
	float3 gui_rotation;
	float3 position;


};

