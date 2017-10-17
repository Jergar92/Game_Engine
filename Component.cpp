#include "Component.h"



Component::Component(GameObject* my_go)
{
	SetMyGO(my_go);
}


Component::~Component()
{
}

void Component::Enable()
{
	enable = true;

}

void Component::Update()
{
}

void Component::GuiDraw()
{
}

void Component::Disable()
{
	enable = false;
}

bool Component::isEnable()
{
	return enable==true;
}

void Component::SetMyGO(GameObject * get)
{
	my_go = get;
}
