#pragma once
#include <string>
class GameObject;
enum ComponentType
{
	TRANSFORM,
	MESH,
	MESH_RENDER,
	CAMERA
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

	virtual void Disable();
	bool isEnable();
	void SetMyGO(GameObject* my_go);
public:
	std::string component_name;
	ComponentType type;
	bool enable = true;
	bool unique=true;

protected:
	GameObject* my_go = nullptr;

};

