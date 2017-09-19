#include "Application.h"
#include "Globals.h"
#include"ModuleConsole.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleConsole::ModuleConsole(Application * app, bool start_enabled) :Module(app, start_enabled)
{
}


ModuleConsole::~ModuleConsole()
{
}

bool ModuleConsole::Start()
{
	bool ret = true;


	return ret;
}

update_status ModuleConsole::PreUpdate(float dt)
{



	return UPDATE_CONTINUE;
}

update_status ModuleConsole::Update(float dt)
{
	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	ImGui::Render();

	
	return UPDATE_CONTINUE;
}

bool ModuleConsole::CleanUp()
{
	bool ret = true;


	return ret;
}

