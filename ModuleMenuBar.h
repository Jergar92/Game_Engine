#pragma once
#include "Application.h"
#include "ModuleMenuBar.h"
#include "Globals.h"
#include"p2Defs.h"


class ModuleMenuBar : public Module
{
public:


	ModuleMenuBar(bool start_enabled = true);
	~ModuleMenuBar();

	bool Start();
	update_status GuiUpdate();

	bool CleanUp();

private:

	void ShowMenuBar();

	bool Draw(bool open);

	void AboutUs();
	void AboutUsWindow();
	bool GetAboutUsStatus();

	void Console();

	void Configuration();
	void Profiler();

private:

	bool  open_console = true;
	bool  open = true;
	bool  show_about_us = false;
	ImVec2 window_about_us_window{ 510,260};
	bool selected[4] = {false,true,false,false};
};


