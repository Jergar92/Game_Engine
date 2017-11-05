#pragma once
#include "Module.h"


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

	//Setters
	void SetPosition(float3 position);

	//Camera Controls and methods
	void LookAt(const float3 & position);
	void Move_Mouse();
	void Orbit(float dx, float dy);
	void Zoom(float zoom);
	void OnClick();

private:
	float3 reference;
	ComponentCamera* camera = nullptr;


};

