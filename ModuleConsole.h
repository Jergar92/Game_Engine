#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui\imgui.h"


class ModuleConsole : public Module
{
public:
	ModuleConsole(bool start_enabled = true);
	~ModuleConsole();

	bool Start();

	bool CleanUp();
	void ClearLog();
	

public:
	
	void ActiveConsole();
	bool GetShowConsole();

	void AddLog(const char*fmt, ...);
	void Draw(const char* tittle);
	
private:
	
	char            inputBuf[256];
	bool            ScrollToBottom;
	int             HistoryPos;
	ImVector<char*> Commands;
	ImVector<char*> History;
	ImVector<char*> Items;
	bool  show_app_console = false;

};