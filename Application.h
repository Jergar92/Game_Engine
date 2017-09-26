#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleConsole.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleScene.h"
#include "ModuleMenuBar.h"
#include "ModuleHardware.h"
//#include "Brofiler\Brofiler.h"
#include <list>

class Application
{
public:
	ModuleWindow*		window;
	ModuleInput*		input;
	ModuleAudio*		audio;
	ModuleRenderer3D*	renderer3D;
	ModuleCamera3D*		camera;
	ModulePhysics3D*	physics;
	ModuleScene*		scene;
	ModuleConsole*      console;
	ModuleMenuBar*		menu_bar;
	ModuleHardware*		hardware;
private: 
	std::string name;
	std::string organization;

	Timer	ms_timer;
	float	dt;
	int		fps = 0;
	int		fps_cap = 0;
	float fps_values[90] = { 0 };
	float millisecons_values[90] = { 0 };

	uint64_t frame_count = 0;
	uint32_t last_sec_frame_count = 0;
	uint32_t prev_last_sec_frame_count = 0;
	uint32_t frames_on_last_update = 0;

	Timer frame_time;
	Timer startup_time;
	Timer last_sec_frame_time;
	std::list<Module*> list_modules;

	bool open_config_window = false;

public:

	Application();
	~Application();
	bool Awake();
	bool Start();
	update_status Update();
	void GuiUpdate(); //void?
	bool CleanUp();
	void LoadConfigWindows();

private:
	
	bool LoadConfigNow();
	bool SaveConfigNow();
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	void SetFPSCap();
};

extern Application* App;