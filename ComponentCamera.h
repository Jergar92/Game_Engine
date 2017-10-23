#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\Frustum.h"
#include "SDL\include\SDL.h"

class ComponentCamera :public Component
{
public:
	ComponentCamera(GameObject* my_go);
	~ComponentCamera();
	bool ObjectInside();
	void InspectorUpdate();
	void Update();

	//Getters
	float GetNearDistance();
	float GetFardistance();
	float3 GetPosition();
	float   GetAspectRatio();

	//Setters
	void SetNearDistance(float distance);
	void SetFarDistance(float distance);

	//Draw
	void DebugDraw();


public:
	
	Frustum camera_frustrum;

private:
	bool enable = false;
	float3 front{ 0, 0, 1 };
	float3 up{ 0,1,0 };
	float3 pos{ 0,0,0 };
	float vertical_fov = 1.0f;
	float window_aspect_ratio;
};

