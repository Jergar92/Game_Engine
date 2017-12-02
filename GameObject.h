#pragma once
#include <vector>
#include <string>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\Quat.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"
#include "MathGeoLib-1.5\src\Geometry\OBB.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "p2Defs.h"
#include "JSONConfig.h"
class Component;
enum GameObjectType
{
	GO_ELEMENT,
	GO_CANVAS
};
enum ComponentType;
class GameObject
{
public:
	GameObject(float3 = float3::one, Quat = Quat::identity, float3 = float3::zero);
	GameObject(GameObject* parent, float3 = float3::one,Quat = Quat::identity, float3 = float3::zero);

	~GameObject();
	void CleanUp();
	void PreUpdate(float dt);

	void Update(float dt);
	void Draw();
	void PostUpdate(float dt);

	void GuiUpdate();
	void InspectorUpdate();
	void OpenStaticQuestion();	

	//Functionality
	void GenerateBoudingBox();
	void RenderBoundingBoxAABB();
	void RenderBoundingBoxOBB();

	void ChangeUID();

	void AddComponent(Component* component_to_add);
	GameObject* CreateChild();
	Component* CreateComponent(ComponentType type);

	Component* FindComponent(ComponentType type, Component* component_to_find)const;
	Component* FindComponent(ComponentType type)const;
	bool HaveComponent(ComponentType type)const;

	void ToDelete();
	void Delete();
	bool RemoveComponent(ComponentType type, int component_position);
	bool RemoveGO(GameObject* to_remove);

	//Setters
	void SetScale(float3 scale);
	void SetRotation(float3 rotation);
	void SetPosition(float3 Position);
	void SetStatic(bool set);
	void SetParent(GameObject * parent);
	void SetChild(GameObject * child);
	void SetName(const char* name);
	void SetTransform(math::float3 scale, math::Quat rotation, math::float3 position);
	void SetAABB(const AABB set_bounding_box);


	//Getters
	float4x4 GetTransposedMatrix() const;
	float4x4 GetGlobalMatrix() const;
	GameObject* GetPartent() const;
	uint GetUID()const;
	uint GetParentUID()const;
	const char* GetName();
	bool GetStatic()const;
	OBB GetBoundingBoxOBB()const;
	AABB GetBoundingBoxAABB()const;
	AABB GetIdentityBoundingBoxAABB() const;
	GameObjectType GetType()const;
	//UpdateMatrix
	void UpdateMatrix();

	//Save&Load
	void LoadGameObject(const JSONConfig& data);
	void SaveGameObject(JSONConfig& data)const;


public:
	std::vector<Component*> components;
	std::vector<GameObject*> childs;

	std::string name;
	std::string input_name;



	float3 scale=float3::one;
	Quat rotation=Quat::identity;
	float3 gui_rotation= float3::zero;
	float3 position = float3::zero;

	

private:
	bool enable = true;
	bool static_go = false;
	bool gui_static = false;
	bool show_bounding_box = false;
	bool is_bounding_box_transformed = false;
	uint UID = 0;
	uint parent_UID = 0;
	GameObjectType type = GO_ELEMENT;
	//AABB bounding box
	OBB global_bounding_box_OBB;
	AABB global_bounding_box_AABB;
	AABB indentity_bounding_box_AABB;
	
	//local transform matrix
	float4x4 transform_matrix = float4x4::identity;
	
	//globals transforms
	float4x4 global_transform_matrix = float4x4::identity;
	float4x4 global_transform_matrix_transposed = float4x4::identity;

	bool to_delete = false;

	GameObject* parent=nullptr;
};

