#pragma once
#include "UI_Windows.h"
#include "Globals.h"

#include "imgui\imgui.h"

class UI_Console : public UI_Windows
{
public:
	UI_Console(ModuleEditorWindows* my_editor);
	~UI_Console();
	bool Draw();
	void CleanUp();
	void ClearLog();
	void ActiveConsole();
	bool GetShowConsole();
	void AddLog(const char*fmt, ...);

private:

	char            inputBuf[256];
	bool            ScrollToBottom;
	int             HistoryPos;
	ImVector<char*> Commands;
	ImVector<char*> History;
	ImVector<char*> Items;
	bool  show_app_console = false;

};

