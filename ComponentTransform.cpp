#include "ComponentTransform.h"



ComponentTransform::ComponentTransform(GameObject* my_go) :Component(my_go)
{
	component_name = "Transform";
}


ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::SetTransform(float3 set_scale, Quat set_rotation, float3 set_position)
{
	scale = set_scale;
	rotation = set_rotation;
	position = set_position;
}

void ComponentTransform::GuiDraw()
{
}
