#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleConsole.h"
#include "ModuleRenderer3D.h"
#include "ModuleTexture.h"
#include "ModuleCamera3D.h"
#include "ModuleScene.h"
#include "ModuleMenuBar.h"
#include "ModuleHardware.h"
#include "Profiler.h"
#include "Primitive_p.h"
//#include "Brofiler\Brofiler.h"
#include <list>

class Application
{
public:
	ModuleWindow*		window;
	ModuleInput*		input;
	ModuleAudio*		audio;
	ModuleRenderer3D*	renderer3D;
	ModuleTexture*		texture;

	ModuleCamera3D*		camera;
	ModuleScene*		scene;
	ModuleConsole*      console;
	ModuleMenuBar*		menu_bar;
	ModuleHardware*		hardware;

	Profiler profiler;

private: 
	std::string name;
	std::string organization;

	Timer	ms_timer;
	float	dt;
	int		fps = 0;
	int		fps_cap = 0;
	float fps_values[40] = { 0 };
	float millisecons_values[40] = { 0 };

	uint64_t frame_count = 0;
	uint32_t last_sec_frame_count = 0;
	uint32_t prev_last_sec_frame_count = 0;
	uint32_t frames_on_last_update = 0;

	Timer frame_time;
	Timer startup_time;
	Timer last_sec_frame_time;
	std::list<Module*> list_modules;

	bool open_config_window = false;
	bool open_profiler_window = false;

public:

	Application();
	~Application();
	bool Awake();
	bool Start();
	update_status Update();
	update_status GuiUpdate();
	void GuiConfigUpdate();

	bool CleanUp();
	void LoadConfigWindows();
	void LoadProfilerWindow();

private:
	char buff[128] = "Aplication Name";
	char buff2[128] = "Organization Name";
	bool LoadConfigNow();
	bool SaveConfigNow();
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	void SetFPSCap();
};

extern Application* App;