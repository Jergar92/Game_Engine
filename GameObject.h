#pragma once
#include <vector>
#include <string>

#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"
class Component;
enum ComponentType;
class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent);

	~GameObject();
	void CleanUp();
	void Update();
	void GuiUpdate();
	void InspectorUpdate();

	void SetParent(GameObject * parent);
	void SetChild(GameObject * child);
	void SetName(const char* name);
	void AddComponent(Component* component_to_add);
	Component* CreateComponent(ComponentType type);
	Component* FindComponent(ComponentType type,Component* component_to_find);
	Component* FindComponent(ComponentType type);


public:
	std::vector<Component*> components;
	std::vector<GameObject*> childs;

	std::string name;
	bool enable;
//	char input_name[128];

	GameObject* parent;

};

