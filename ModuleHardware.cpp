#include "Globals.h"
#include "Application.h"
#include "ModuleHardware.h"

ModuleHardware::ModuleHardware(bool start_enabled)
{
	name = "Hardware";
}

ModuleHardware::~ModuleHardware()
{
}

bool ModuleHardware::Awake(const JSON_Object * data)
{
	bool ret = true;
	return ret;
}

bool ModuleHardware::Start()
{
	bool ret = true;
	return ret;
}

bool ModuleHardware::CleanUp()
{
	bool ret = true;
	return ret;
}

void ModuleHardware::GuiUpdate()
{
	if (ImGui::CollapsingHeader(name.c_str()))
	{

	}
}
