#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleImporter.h"
#include "MathGeoLib-1.5/src/Algorithm/Random/LCG.h"
class ModuleFileSystem;
class ModuleWindow;
class ModuleInput;
class ModuleAudio;
class ModuleImporter;
class ModuleRenderer3D;
class ModuleCamera3D;
class ModuleScene;
class ModuleConsole;
class ModuleEditorWindows;
class ModuleHardware;
class Profiler;

#include <list>
#define HISTOGRAM_LIMIT 40

class Application
{
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
	void CalculeFPSHistogram();
	void CalculeMSHistogram();
	int GenerateRandom();
private:

	bool LoadConfigNow();
	bool SaveConfigNow();
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	void SetFPSCap();

public:

	ModuleFileSystem*	file_system;
	ModuleWindow*		window;
	ModuleInput*		input;
	ModuleAudio*		audio;
	ModuleRenderer3D*	renderer3D;
	ModuleImporter*		importer;
	ModuleCamera3D*		camera;
	ModuleScene*		scene;
	ModuleConsole*      console;
	ModuleEditorWindows* editor_window;
	ModuleHardware*		hardware;

	Profiler* profiler;
private:
	std::string name;
	std::string organization;
	char buff[128] = "Aplication Name";
	char buff2[128] = "Organization Name";
	Timer	ms_timer;
	float	dt;
	int		fps = 0;
	int		fps_cap = 0;
	//this +1 is for histogram loop
	float fps_values[HISTOGRAM_LIMIT + 1] = { 0 };
	float millisecons_values[HISTOGRAM_LIMIT + 1] = { 0 };

	uint64_t frame_count = 0;
	uint32_t last_sec_frame_count = 0;
	uint32_t prev_last_sec_frame_count = 0;
	uint32_t frames_on_last_update = 0;

	Timer frame_time;
	Timer startup_time;
	Timer last_sec_frame_time;
	std::list<Module*> list_modules;

	LCG random;

	bool open_config_window = false;
	bool open_profiler_window = false;
};

extern Application* App;