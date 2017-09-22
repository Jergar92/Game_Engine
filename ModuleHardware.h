#pragma once

#include "Module.h"
#include "Globals.h"

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

};