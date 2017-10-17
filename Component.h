#pragma once
#include "GameObject.h"
#include <string>
class GameObject;
enum ComponentType
{
	TRANSFORM,
	MESH,
	MESH_RENDER
};
class Component
{
public:
	Component(GameObject* my_go);
	~Component();
	virtual void Enable();
	virtual void Update();
	virtual void GuiDraw();

	virtual void Disable();
	bool isEnable();
	void SetMyGO(GameObject* my_go);
public:
	std::string component_name;
	ComponentType type;
	bool enable = true;
	bool unique=true;
private:
	GameObject* my_go = nullptr;

};

