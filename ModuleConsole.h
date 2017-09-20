#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class ModuleConsole : public Module
{
public:
	ModuleConsole(Application* app, bool start_enabled = true);
	~ModuleConsole();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	void ClearLog();
	

public:
	
	void AddLog(const char*fmt, ...);
	void Draw(const char* tittle,bool* p_open);

	

private:
	char            inputBuf[256];
	bool            ScrollToBottom;
	int             HistoryPos;
	ImVector<char*> Commands;
	ImVector<char*> History;
	ImVector<char*> Items;
	bool  show_app_console = false;

};