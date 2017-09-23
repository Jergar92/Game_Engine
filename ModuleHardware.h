#pragma once

#include "Module.h"
#include "Globals.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class ModuleHardware : public Module
{
public:
	ModuleHardware(bool start_enabled = true);
	~ModuleHardware();

	bool Awake(const JSON_Object* data);
	bool Start();
	bool CleanUp();
	void GuiUpdate();


private:
	SDL_version sdl_vers;
	int cpu_numbers = 0;
	int cpu_cache = 0;
	int system_ram = 0;
};