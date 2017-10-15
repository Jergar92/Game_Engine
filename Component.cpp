#include "Component.h"



Component::Component()
{
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
