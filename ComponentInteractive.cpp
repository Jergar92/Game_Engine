#include "ComponentInteractive.h"
#include "GameObject.h"


ComponentInteractive::ComponentInteractive(GameObject* my_go):Component(my_go)
{
	transform = (ComponentRectTransform*)my_go->FindComponent(RECT_TRANSFORM);
}


ComponentInteractive::~ComponentInteractive()
{
}

void ComponentInteractive::OnIdle()
{
	
}

void ComponentInteractive::OnHover()
{
	states = HOVER;
	Hover();
}
