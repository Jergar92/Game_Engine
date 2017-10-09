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
public:
	std::vector<Component*> components;
	std::string name;
	bool enable;
	GameObject* parent;

};

