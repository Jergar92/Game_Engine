#pragma once
#include "Component.h"
#include "ComponentInteractive.h"
class ComponentText;
class ComponentInputText:public ComponentInteractive
{
public:
	ComponentInputText(GameObject* my_go);
	~ComponentInputText();

private:
	ComponentText* my_text = nullptr;
};

