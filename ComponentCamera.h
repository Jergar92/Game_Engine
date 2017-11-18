#pragma once
#include "Component.h"
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\Frustum.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"
#include "SDL\include\SDL.h"
#include <list>

class GameObject;
class ComponentCamera :public Component
{
public:
	ComponentCamera(GameObject* my_go);
	~ComponentCamera();
	bool ObjectInside();
	void InspectorUpdate();
	void Update(float dt);
	void OnUpdateMatrix(const float4x4 & matrix);

	//Culling
	void Culling();
	GameObject* SetElementsOnScene();
	void EnableDraw(bool draw);
	void CheckForMeshQuadtree(GameObject* scene);

	//Getters
	float GetNearDistance() const;
	float GetFardistance()const;
	float3 GetPosition()const;
	float   GetAspectRatio()const;
	float* GetViewMatrix()const;
	float* GetProjectionMatrix()const;
	bool GetEnableCulling()const;

	//Setters
	void SetNearDistance(float distance);
	void SetFarDistance(float distance);
	void SetAspectRatio();
	void UpdateMatrix();
	//Save&Load
	bool SaveComponent(JSONConfig& data)const;
	bool LoadComponent(const JSONConfig& data);

	void Look(const float3 & position);



	//Draw
	void DebugDraw();


public:
	
	Frustum camera_frustrum;
	bool matrix_update = false;
	
private:

	bool enable_culling = false;
	bool enable_camera_render = false;
	float vertical_fov = 1.0f;
	float window_aspect_ratio;
	GameObject* scene;
	float4x4 view_matrix;
	float4x4 projetion_matrix;
	std::list<GameObject*>static_list;
	std::list<GameObject*>::iterator iterator_go;
};

