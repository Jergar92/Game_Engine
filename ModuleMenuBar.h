#pragma once
#include "Application.h"
#include "ModuleMenuBar.h"
#include "Globals.h"
#include"p2Defs.h"

class GameObject;
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
private:
	bool ShowEditor();
	bool ShowInspector();
	bool ShowHierarchy();

	bool ShowMenuBar();

	bool Draw(bool open);

	void AboutUs();
	void AboutUsWindow();
	bool GetAboutUsStatus()const;

	void Console();

	void Configuration();
	void Profiler();


private:
	GameObject* scene_go=nullptr;
	GameObject* selected_go = nullptr;
	bool inspector = true;
	bool hierarchy = true;

	
	bool  open_console = true;
	bool  open = true;
	bool  show_about_us = false;
	bool selected[4] = {false,true,false,false};
};


