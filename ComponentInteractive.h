#pragma once

#include "Component.h"
class ComponentRectTransform;
enum States
{
	IDLE,
	HOVER,
	DOWN,
};

class ComponentInteractive : Component
{

public:

	ComponentInteractive(GameObject* my_go);
	~ComponentInteractive();
	
	void OnIdle();
	void OnHover();
	void OnClick();
	void OnDown();
	void OnDrag();

	virtual void Hover() = 0;

public:

	States states = IDLE;
	ComponentRectTransform* transform;

private:

	bool is_dragable = false;


};

