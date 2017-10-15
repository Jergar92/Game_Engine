#pragma once
#include "Component.h"
class ComponentTransform:public Component
{
public:
	ComponentTransform();
	~ComponentTransform();

	void GuiDraw();
};

