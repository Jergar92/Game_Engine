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
	
	//Getters
	float4x4 GetInverseMatrix() const;
	float4x4 GetTransposedMatrix() const;
	float4x4 GetGlobalMatrix() const;
	float Getdepth()const;
	float2 GetPivot() const;
	float3   GetSouthWest() const;
	float3   GetNorthWest() const;
	float3   GetSouthEast() const;
	float3   GetNorthEeast() const;

	//Setters
	void SetBlock(bool block);

	void SetScale(float3 scale);
	
	float GetWidth() const;
	float GetHeight() const;
	float GetDepth()const;

	void SetRotation(float3 rotation);
	void SetPosition(float3 Position);
	void SetWidth(float width);
	void SetHeight(float height);

	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

public:

	float3 scale = float3::one;
	Quat rotation = Quat::identity;
	float3 gui_rotation = float3::zero;
	float3 position = float3::zero;
	bool update = false;
	float3 value = float3::zero;
	bool block = false;
private:

	float4x4 transform_matrix;
	float4x4 transform_matrix_transposed;

	//globals transforms
	float4x4 global_transform_matrix = float4x4::identity;
	float4x4 global_transform_matrix_transposed = float4x4::identity;

	//2D Transforms
	float width = 100.0f;
	float height = 100.0f;

	//pivot init on center point on the item
	float2 pivot{ 0.5f,0.5f };

	//depth
	float depth = 0;
};