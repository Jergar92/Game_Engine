#pragma once
#include "Application.h"
#include "ModuleMenuBar.h"
#include "Globals.h"
#include"p2Defs.h"

class GameObject;
class UI_Windows;
class UI_Inspector;
class UI_Hierarchy;
class UI_About;
class UI_Console;

class ModuleMenuBar : public Module
{
public:


	ModuleMenuBar(bool start_enabled = true);
	~ModuleMenuBar();

	bool Start();
	update_status GuiUpdate();

	bool CleanUp();

	void SetSceneGameObject(GameObject* set);
	void SetSelectedGameObject(GameObject* set);
	void AddLog(const char*fmt, ...);

private:

	bool ShowMenuBar();
	void Configuration();
	void Profiler();
private:
	std::vector<UI_Windows*> ui_windows;
	UI_Inspector* ui_inspector;
	UI_Hierarchy* ui_hierarchy;
	UI_About* ui_about;
	UI_Console* ui_console;

	bool inspector = true;
	bool hierarchy = true;

	
	bool  open_console = true;
	bool  open = true;
	bool  show_about_us = false;
	bool selected[4] = {false,true,false,false};
};


