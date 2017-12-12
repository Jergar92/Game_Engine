#pragma once
#ifndef __COMPONENT_BUTTON__
#define __COMPONENT_BUTTON__
#include "Component.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
class ComponentImage;

struct Vector2f {

	float x;
	float y;
};
struct State {
	
	float2 uv0;
	float2 uv1;
	void SetCoords(float2 uv0, float2 uv1);
};
enum ButtonState{IDLE,OVER,CLICKED};

class ComponentButton : public Component
{

public:

	ComponentButton(GameObject* my_go);
	~ComponentButton();

	void Update(float dt);

	void InspectorUpdate();
	void SetState(ButtonState status);

private:

	ComponentImage* texture = nullptr;
	State idle, over, pressed;
	ButtonState status;
};


/*
idle	(0,220),(890,0)
over (895 220) (1786,0)
click (1793,220), (2684,0)
*/
#endif // __COMPONENT_BUTTON__

