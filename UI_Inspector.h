#pragma once
#include "UI_Windows.h"
class GameObject;
class Resource;
enum InspectorShow
{
	I_NONE,
	I_GO,
	I_RESOURCE,
	
};
class UI_Inspector:public UI_Windows
{
public:
	UI_Inspector(ModuleEditorWindows* my_editor);
	~UI_Inspector();
	bool Draw();
	void CleanUp();
	void SetSelectedGameObject(GameObject* set);
	void SetSelectedResource(Resource* set);

	GameObject* GetSelected()const;

	void InspectorGameObject();
	void InspectorResource();

public:
	GameObject* selected_go = nullptr;
	Resource* selected_resource = nullptr;
	InspectorShow show = I_NONE;

};

