#include "Application.h"
#include "p2Defs.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	scene = new ModuleScene(this);
	console = new ModuleConsole(this);
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	AddModule(audio);
	AddModule(physics);

	//console module
	AddModule(console);
	
	//Scene Module
	AddModule(scene);
	
	
	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	std::list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end())
	{
		RELEASE(item._Ptr->_Myval);
	    item++;
	}

	
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	std::list<Module*>::iterator item = list_modules.begin();

	if (ret == true)
	{
		while (item != list_modules.end() && ret == true)
		{
			ret = item._Ptr->_Myval->Init();
		    item++;
		}
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->Start();
		item++;
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	static bool no_titlebar = true;

	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;	
	}

	if (ret == UPDATE_CONTINUE) {
		GuiUpdate(&no_titlebar);

	}


	item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::iterator item = list_modules.end();
	

	while(item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->CleanUp();
		item--;
	}
	return ret;
}

bool Application::LoadGameNow()
{
	bool ret = false;

	return ret;
}

bool Application::SaveGameNow()
{
	bool ret = true;

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::GuiUpdate(bool* open)
{
	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
	if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
	if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Configuration", open, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Application"))
	{

	}

	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		
		item._Ptr->_Myval->GuiUpdate();
		item++;
	}

	ImGui::End();

}