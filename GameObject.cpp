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

void GameObject::GuiUpdate()
{
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];
			item->GuiDraw();
	}
}

void GameObject::AddComponent(Component * component_to_add)
{
	components.push_back(component_to_add);
}

Component* GameObject::FindComponent(ComponentType type, Component * component_to_find)
{
	Component* ret = nullptr;
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];

		if (item->type == type)
		{
			if (item == component_to_find)
			{
				ret = item;
				return item;
			}
		}
	}
	return ret;
}

Component* GameObject::FindComponent(ComponentType type)
{
	Component* ret = nullptr;
	for (int i = 0; i < components.size(); i++)
	{
		Component* item = components[i];

		if (item->type == type)
		{
			ret = item;
			return item;
		}
	}
	return ret;
}
