#pragma once
#include "Globals.h"
#include "Component.h"
#include "ComponentInteractive.h"
class ComponentText;

class ComponentInputText:public ComponentInteractive
{
public:
	ComponentInputText(GameObject* my_go);
	~ComponentInputText();
	void OnStart();
	void OnStop();
	void AddText(const char* str);
	void AddText(const char* str, uint position);
	bool EraseText(uint position);
	void MoveRight();
	void MoveLeft();
	void MoveToEnd();
	void MoveToStart();
	void CallUpdate();

	void Idle();
	void Hover();
	void Down();

	uint GetCurrentPos()const;
	void ReduceCursorPos();
private:
	uint cursor_pos = 0;

	ComponentText* my_text = nullptr;
	ComponentCanvas* canvas = nullptr;

};

