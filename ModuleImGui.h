#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"


class ModuleImGui: public Module
{
public:
	ModuleImGui(Application* app, bool  start_enabled = true);
	~ModuleImGui();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	
	bool CleanUp();

private:
	bool show_test_window = true;
	bool show_another_window = false;
	bool show_prove_window = false;
	int i0 = 0;
	int i1 = 0;
	int i2 = 0;
	
	ImVec4 clear_color = ImColor(114, 144, 154);
};

