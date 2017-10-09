#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
		if(item->isEnable())
			item->Update();
	}
}
