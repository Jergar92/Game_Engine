#include "ComponentButton.h"
#include "Application.h"
#include "ModuleInput.h"
#include "GameObject.h"

ComponentButton::ComponentButton(GameObject* my_go) : Component(my_go)
{
	component_name = "Button";
	type = CANVAS_BUTTON;
	texture = (ComponentImage*)my_go->FindComponent(ComponentType::CANVAS_IMAGE);	// = nullptr; //WIP
}

ComponentButton::~ComponentButton()
{

}

void ComponentButton::Update()
{
	//Needs improvement to not be constantly called every frame (only when moving mouse)
	if (0)//WIP
	{

	}
}
