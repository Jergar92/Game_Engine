#pragma once

#include "Component.h"
class ComponentRectTransform;
class ComponentCanvas;
enum States
{
	IDLE,
	HOVER,
	DOWN,
};

class ComponentInteractive : public Component
{

public:

	ComponentInteractive(GameObject* my_go);
	~ComponentInteractive();
	
	//Interactive function states
	void OnIdle();
	void OnHover();
	void OnClick();
	void OnDown();

	void SetCurrentFocus(bool state);


	ComponentCanvas* FindMyCanvas();
	
	virtual void Idle() = 0;
	virtual void Hover() = 0;
	virtual void Down() = 0;

public:

	States states = IDLE;
	States last_state = IDLE;

	ComponentRectTransform* transform;

	bool on_execution = false;
	bool is_dragable = false;
	bool is_focusable = false;
	bool has_focus = false;

	ComponentCanvas* canvas = nullptr;
};

