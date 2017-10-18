#pragma once
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\Quat.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"

class ComponentTransform :public Component
{
public:
	ComponentTransform(GameObject* my_go);
	~ComponentTransform();
	void SetTransform(float3 scale, Quat rotation, float3 position);
	void GuiUpdate();
	void InspectorUpdate();

	//Update Matrix
	void UpdateMatrix();
	float4x4 GetInverseMatrix() const;

	//Setters
	void SetScale(float3 scale);
	void SetRotation(float3 rotation);

public:
	float3 scale;
	Quat rotation;
	float3 gui_rotation;
	float3 position;

private:
	float4x4 transform_matrix;
	float4x4 transform_matrix_inverse;

};

