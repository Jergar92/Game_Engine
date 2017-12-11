#pragma once
#ifndef __COMPONENT_BUTTON__
#define __COMPONENT_BUTTON__
#include "Component.h"
class ComponentImage;

struct Vector2f {

	float x;
	float y;
};
struct State {

	Vector2f uv0;
	Vector2f uv1;
};
enum ButtonState{IDLE,OVER,CLICKED};

class ComponentButton : public Component
{

public:

	ComponentButton(GameObject* my_go);
	~ComponentButton();

	void Update();

private:

	ComponentImage* texture = nullptr;
	State idle, over, pressed;
	ButtonState status = IDLE;
};


/*
idle	(0,220),(890,0)
over (895 220) (1786,0)
click (1793,220), (2684,0)
*/
#endif // __COMPONENT_BUTTON__

