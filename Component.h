#pragma once
#include <string>
#include "Globals.h"
#include "JSONConfig.h"

class GameObject;

enum ComponentType
{

	TRANSFORM,
	MESH,
	MESH_RENDER,
	CAMERA,
	NO_COMPONENT
};
class Component
{
public:
	Component(GameObject* my_go);
	~Component();
	virtual void Enable();
	virtual void CleanUp();
	virtual void Update();
	virtual void GuiUpdate();
	virtual void InspectorUpdate();
	virtual bool SaveComponent(JSONConfig& data)const;
	virtual bool LoadComponent(const JSONConfig & data);
	virtual void OnUpdateMatrix(const float4x4 & matrix);

	virtual void Disable();
	bool isEnable();
	void SetMyGO(GameObject* my_go);
public:
	std::string component_name;
	ComponentType type;
	bool enable = true;
	bool unique=true;
	GameObject* my_go = nullptr;
protected:
	uint UUID = 0;
};

