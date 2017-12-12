#pragma once
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\Quat.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"

class ComponentRectTransform :public Component
{
public:
	ComponentRectTransform(GameObject* my_go, float3 scale = float3::one, Quat rotation = Quat::identity, float3 position = float3::zero);
	~ComponentRectTransform();
	void SetTransform(float3 scale, Quat rotation, float3 position);
	void GuiUpdate();
	void InspectorUpdate();

	//Update Matrix
	void UpdateMatrix();

	float4x4 GetInverseMatrix() const;
	float4x4 GetTransposedMatrix() const;
	float4x4 GetGlobalMatrix() const;

	//Setters
	void SetScale(float3 scale);
	void SetRotation(float3 rotation);
	void SetPosition(float3 Position);

	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

public:

	float3 scale = float3::one;
	Quat rotation = Quat::identity;
	float3 gui_rotation = float3::zero;
	float3 position = float3::zero;

private:

	float4x4 transform_matrix;
	float4x4 transform_matrix_transposed;

	//globals transforms
	float4x4 global_transform_matrix = float4x4::identity;
	float4x4 global_transform_matrix_transposed = float4x4::identity;

};