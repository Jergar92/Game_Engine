#pragma once
#include "UI_Windows.h"
class GameObject;
enum InspectorShow
{
	I_GO,
	I_MESH,
	I_TEXTURE
};
class UI_Inspector:public UI_Windows
{
public:
	UI_Inspector();
	~UI_Inspector();
	bool Draw();
	void CleanUp();
	void SetSelectedGameObject(GameObject* set);

	void InspectorGameObject();
public:
	GameObject* selected_go = nullptr;
	InspectorShow show = I_GO;

};

