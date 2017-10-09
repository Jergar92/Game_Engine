#pragma once
#include <vector>
#include <string>

#include "Component.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	void AddComponent(Component* component_to_add);
	Component* FindComponent(ComponentType type,Component* component_to_find);
	Component* FindComponent(ComponentType type);


public:
	std::vector<Component*> components;
	std::string name;
	bool enable;
	GameObject* parent;

};

