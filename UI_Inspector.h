#pragma once
#include "UI_Windows.h"
class GameObject;
class UI_Inspector:public UI_Windows
{
public:
	UI_Inspector();
	~UI_Inspector();
	bool Draw();
	void SetSelectedGameObject(GameObject* set);
public:
	GameObject* selected_go = nullptr;
};

