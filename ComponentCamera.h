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
	void OnUpdateMatrix(const float4x4 & matrix);

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
	float vertical_fov = 1.0f;
	float window_aspect_ratio;
	GameObject* scene;
};

