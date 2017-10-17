#pragma once
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Geometry\Frustum.h"

class ComponentCamera :public Component
{
public:
	ComponentCamera(GameObject* my_go);
	~ComponentCamera();
	bool ObjectInside();
public:
	Frustum camera_frustrum;
};

