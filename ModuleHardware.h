#pragma once

#include "Module.h"
#include "Globals.h"


class ModuleHardware : public Module
{
public:
	ModuleHardware(bool start_enabled = true);
	~ModuleHardware();

	bool Start();
	bool CleanUp();
	void GuiConfigUpdate();

private:
	SDL_version sdl_vers;
	int cpu_numbers = 0;
	int cpu_cache = 0;
	int system_ram = 0;
};