#pragma once
#include "Component.h"
#include "ComponentMesh.h"
class ComponentMeshRenderer:public Component
{
public:
	ComponentMeshRenderer();
	~ComponentMeshRenderer();
public:
	void Update();
	ComponentMesh* mesh = nullptr;
};

