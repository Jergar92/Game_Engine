#pragma once
#include "GameObject.h"
#include <string>
class GameObject;
enum ComponentType
{
	TRANSFORM,
	MESH,
	MATERIAL
};
class Component
{
public:
	Component();
	~Component();
	virtual void Enable();
	virtual void Update();
	virtual void GuiDraw();

	virtual void Disable();
	bool isEnable();
public:
	GameObject* my_go=nullptr;
	std::string component_name;
	ComponentType type;
	bool enable = true;
	bool unique=true;

};

