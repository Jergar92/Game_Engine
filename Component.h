#pragma once
#include <string>
#include "Globals.h"
#include "JSONConfig.h"

class GameObject;

enum ComponentType
{
	RECT_TRANSFORM = -2,
	TRANSFORM = -1,
	NO_COMPONENT = 0,
	MESH,
	MESH_RENDER,
	CAMERA,
	CANVAS,
	CANVAS_RENDER,
	CANVAS_TEXT,
	CANVAS_INPUT_TEXT,
	CANVAS_IMAGE,
	CANVAS_BUTTON,
	CANVAS_CHECKBOX,
	CANVAS_IMDRAG
};
class Component
{
public:
	Component(GameObject* my_go);
	virtual ~Component();
	virtual void Enable();
	virtual void OnPlay();
	virtual void OnStop();

	virtual void CleanUp();
	virtual void Update(float dt);
	virtual void GuiUpdate();
	virtual void InspectorUpdate();
	virtual bool SaveComponent(JSONConfig& data)const;
	virtual bool LoadComponent(const JSONConfig & data);
	virtual void OnUpdateMatrix(const float4x4 & matrix);

	virtual void Disable();
	void DeleteComponent();
	bool ToDelete()const;
	bool isEnable();
	void SetMyGO(GameObject* my_go);
public:
	std::string component_name;
	ComponentType type;
	bool enable = true;
	bool unique=true;
	bool to_delete = false;
	GameObject* my_go = nullptr;
protected:
	uint UUID = 0;
};

