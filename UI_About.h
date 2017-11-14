#pragma once
#include "UI_Windows.h"
class UI_About : public UI_Windows
{
public:
	UI_About(ModuleEditorWindows* my_editor);
	~UI_About();
	bool Draw();
	bool selected[4] = { false,true,false,false };

};

