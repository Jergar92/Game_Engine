#pragma once
#include "GameObject.h"
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

	virtual void Disable();
	bool isEnable();
public:
	GameObject* my_go=nullptr;
	ComponentType type;
	bool enable = true;
	bool unique=true;

};

