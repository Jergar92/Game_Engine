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
private: 
	std::string name;
	std::string organization;

	Timer	ms_timer;
	float	dt;
	int		fps = 0;
	int		fps_cap = 0;


	uint64_t frame_count = 0;
	uint32_t last_sec_frame_count = 0;
	uint32_t prev_last_sec_frame_count = 0;
	uint32_t frames_on_last_update = 0;

	Timer frame_time;
	Timer startup_time;
	Timer last_sec_frame_time;
	std::list<Module*> list_modules;

public:

	Application();
	~Application();
	bool Awake();
	bool Init();
	update_status Update();
	void GuiUpdate(bool* open); //void?
	bool CleanUp();

private:
	bool LoadGameNow();
	bool SaveGameNow();
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;