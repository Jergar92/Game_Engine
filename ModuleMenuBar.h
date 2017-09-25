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
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();

private:

	void ShowMenuBar();
	
	bool Draw(bool open);

	void AboutUs();
	void AboutUsWindow();
	bool GetAboutUsStatus();

	void Console();

	void Configuration();

private:

	bool  open_console = true;
	bool  open = true;
	bool  show_about_us = false;
	
};

