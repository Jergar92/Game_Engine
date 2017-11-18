#pragma once
#include "Module.h"
#include "MathGeoLib-1.5\src\Geometry\LineSegment.h"
#include <map>
#include <vector>
class GameObject;
class ComponentCamera;

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Start();
	bool CleanUp();
	update_status Update(float dt);

	//Getters
	float3 GetPosition() const;
	float3 GetReference() const;
	ComponentCamera * GetCamera() const;
	bool GetRaycast()const;

	//Setters
	void SetPosition(float3 position);

	//Camera Controls and methods 
	void LookAt(const float3 & position);
	void MoveMouse();
	void MoveKeyBoard(float dt);
	void Orbit(float dx, float dy);
	void Rotate(float dx, float dy);
	void Focus(GameObject * Clicked);
	void Zoom(float zoom);
	void OnClick();
	void OnCollision();
	void GameObjectsChilds(GameObject* go,std::map<float,GameObject*>&);
	bool EnableRaycast();

private:
	float3 reference;
	float3 new_pos = { 0, 0, 0 };
	bool show_raycast = false;
	bool enable_left = false;
	ComponentCamera* camera = nullptr;
	LineSegment ray = LineSegment(float3::zero,float3::zero);
	
};

