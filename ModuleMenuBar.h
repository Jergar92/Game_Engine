#pragma once
#include "Application.h"
#include "ModuleMenuBar.h"
#include "Globals.h"
#include"p2Defs.h"
#include "imgui\imgui.h"


class ModuleMenuBar : public Module
{
public:


	ModuleMenuBar(bool start_enabled = true);
	~ModuleMenuBar();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();

private:

	void ShowMenuBar();
	
	bool GetUpdateStatus();
	void StopUpdate();

	void AboutUs();
	void AboutUsWindow();
	bool GetAboutUsStatus();

	void Console();

	void Configuration();

private:

	bool  open_console = true;
	bool  open = true;
	bool  stop_update = false;
	bool  show_about_us = false;

};

