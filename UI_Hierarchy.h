#pragma once
#include "UI_Windows.h"
class GameObject;

class UI_Hierarchy:public UI_Windows
{
public:
	UI_Hierarchy();
	~UI_Hierarchy();
	bool Draw();
	void CleanUp();
	void SetSceneGameObject(GameObject* set);
public:
	GameObject* scene_go = nullptr;

};

