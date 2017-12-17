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
	void OnPlay();
	void OnStop();
	void CleanUp();
	bool SaveComponent(JSONConfig & config) const;

	bool LoadComponent(const JSONConfig & config);
	void AddText(const char* str);
	void AddText(const char* str, uint position);
	bool EraseTextBack(uint position);
	bool EraseTextFront(uint position);

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

};

