#pragma once
#include "UI_Windows.h"
class UI_About : public UI_Windows
{
public:
	UI_About();
	~UI_About();
	bool Draw();
	bool selected[4] = { false,true,false,false };

};

