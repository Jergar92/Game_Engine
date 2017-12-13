#pragma once
class ModuleEditorWindows;
class UI_Windows
{
public:
	UI_Windows(ModuleEditorWindows* my_editor);
	virtual ~UI_Windows();

	virtual bool Draw();
	virtual void CleanUp();

	bool IsActive()const;
	void ChangeActive();
public:
	bool active_draw = true;
protected:
	ModuleEditorWindows* my_editor = nullptr;
};

