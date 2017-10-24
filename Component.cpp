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
void Component::CleanUp()
{
}

void Component::Update()
{
}

void Component::GuiUpdate()
{
}

void Component::InspectorUpdate()
{
}

bool Component::SaveComponent(const JSON_Object * data)
{
	return false;
}


void Component::Load()
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
