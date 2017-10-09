#pragma once
#include "GameObject.h"
class Component
{
public:
	Component();
	~Component();
	virtual void Enable();
	virtual void Update();

	virtual void Disable();
public:
	GameObject* my_go;
	bool enable;

};

