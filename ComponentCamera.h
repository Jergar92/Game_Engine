#pragma once
#include "Component.h"
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\Frustum.h"
#include "SDL\include\SDL.h"
class GameObject;
class ComponentCamera :public Component
{
public:
	ComponentCamera(GameObject* my_go);
	~ComponentCamera();
	bool ObjectInside();
	void InspectorUpdate();
	void Update();

	//Culling
	void Culling();
	GameObject* SetElementsOnScene();
	void CheckForMesh(GameObject* scene);

	//Getters
	float GetNearDistance() const;
	float GetFardistance()const;
	float3 GetPosition()const;
	float   GetAspectRatio()const;

	//Setters
	void SetNearDistance(float distance);
	void SetFarDistance(float distance);
	void SetAspectRatio();

	//Save&Load
	bool SaveComponent(JSONConfig& data)const;

	//Draw
	void DebugDraw();


public:
	
	Frustum camera_frustrum;
	
private:
	float3 front{ 0, 0, 1 };
	float3 up{ 0,1,0 };
	float3 pos{ 0,0,0 };
	float vertical_fov = 1.0f;
	float window_aspect_ratio;
	GameObject* scene;
};

