#pragma once
#include <vector>
#include <string>

#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"
class Component;
enum z;
class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent);

	~GameObject();
	void Update();
	void GuiUpdate();
	void SetParent(GameObject * parent);
	void SetChild(GameObject * child);

	void AddComponent(Component* component_to_add);
	Component* CreateComponent(ComponentType type);
	Component* FindComponent(ComponentType type,Component* component_to_find);
	Component* FindComponent(ComponentType type);


public:
	std::vector<Component*> components;
	std::vector<GameObject*> childs;

	std::string name;
	bool enable;
	GameObject* parent;

};

