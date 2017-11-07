#include "Application.h"
#include "p2Defs.h"
#include "mmgr\mmgr.h"
#include "ModuleFileSystem.h"
#include "ModuleImporter.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera.h"
#include "ModuleScene.h"
#include "ModuleEditorWindows.h"
#include "ModuleHardware.h"
#include "Profiler.h"
Application::Application()
{
	file_system = new ModuleFileSystem();
	window = new ModuleWindow();
	input = new ModuleInput();
	audio = new ModuleAudio();
	importer = new ModuleImporter();
	renderer3D = new ModuleRenderer3D();
	scene = new ModuleScene();
	camera = new ModuleCamera();
	editor_window = new ModuleEditorWindows();
	hardware = new ModuleHardware();
	
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order
	profiler = new Profiler;
	profiler->CreateFrame("Application_Start");

	// Main Modules
	
	AddModule(file_system);
	profiler->CreateTitle("Application_Start", file_system->name.c_str());

	AddModule(window);
	profiler->CreateTitle("Application_Start",window->name.c_str());

	AddModule(camera);
	profiler->CreateTitle("Application_Start",camera->name.c_str());

	AddModule(input);
	profiler->CreateTitle("Application_Start",input->name.c_str());

	AddModule(audio);
	profiler->CreateTitle("Application_Start",audio->name.c_str());


	AddModule(importer);
	profiler->CreateTitle("Application_Start", importer->name.c_str());



	//Scene Module
	AddModule(scene);
	profiler->CreateTitle("Application_Start",scene->name.c_str());

	AddModule(hardware);
	profiler->CreateTitle("Application_Start",hardware->name.c_str());

	AddModule(editor_window);
	profiler->CreateTitle("Application_Start",editor_window->name.c_str());

	
	// Renderer last!
	AddModule(renderer3D);
	profiler->CreateTitle("Application_Start",renderer3D->name.c_str());

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

bool Application::Awake()
{
	bool ret = true;
	JSONConfig config;
	// Call Awake() in all modules
	if (!config.ParseFile("config.json",file_system->GetSettingsFolder()))
	{
		ret = false;
	}

	if (ret == true)
	{
		open_config_window = false;
		JSONConfig app_config = config.SetFocus("App");

		name = app_config.GetString("name");
		organization = app_config.GetString("organization");
		fps_cap = app_config.GetInt("frame_cap");

		std::list<Module*>::iterator item = list_modules.begin();
		while (item != list_modules.end() && ret == true)
		{

			profiler->CreateCategory("Application_Start",item._Ptr->_Myval->name.c_str(), "Awake");
			ret = item._Ptr->_Myval->Awake(config.SetFocus(item._Ptr->_Myval->name.c_str()));
			item++;
		}
		profiler->StopCurrentCategory();
		config.CleanUp();

	}
	return ret;
}

bool Application::Start()
{
	bool ret = true;
	LOG("Application Start --------------");
	std::list<Module*>::iterator item = list_modules.begin();

	item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		profiler->CreateCategory("Application_Start",item._Ptr->_Myval->name.c_str(), "Start");
		ret = item._Ptr->_Myval->Start();
		item++;
	}
	profiler->StopCurrentCategory();
	profiler->CreateFrame("Application_Update");
	profiler->CopyTitle("Application_Start","Application_Update");
	profiler->CreateTitle("Application_Update", "FinishUpdate");

	SetFPSCap();
	startup_time.Start();
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;
	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{


	profiler->CreateCategory("Application_Update", "FinishUpdate", "delay");


	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		CalculeFPSHistogram();
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	CalculeMSHistogram();
	uint32_t last_frame_ms = frame_time.Read();
	frames_on_last_update = prev_last_sec_frame_count;


	if (fps > 0 && last_frame_ms < fps)
	{
		SDL_Delay(fps - last_frame_ms);
	}
}

void Application::SetFPSCap()
{
		fps = (fps_cap > 0) ? 1000 / fps_cap : 0;
	
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	PrepareUpdate();
	
	std::list<Module*>::iterator item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		profiler->CreateCategory("Application_Update",item._Ptr->_Myval->name.c_str(), "PreUpdate");

		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;	
	}

	item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		profiler->CreateCategory("Application_Update",item._Ptr->_Myval->name.c_str(), "Update");
		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}
	
	if (ret == UPDATE_CONTINUE) {
		ret = GuiUpdate();
	}

	item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		profiler->CreateCategory("Application_Update",item._Ptr->_Myval->name.c_str(), "PostUpdate");

		ret = item._Ptr->_Myval->PostUpdate(dt);
		item++;
	}
	profiler->StopCurrentCategory();

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	RELEASE(profiler);

	std::list<Module*>::reverse_iterator item = list_modules.rbegin();
	while(item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
	}
	return ret;
}

void Application::LoadConfigWindows()
{
	open_config_window = !open_config_window;
}

void Application::LoadProfilerWindow()
{
	profiler->OpenWindows();

}

void Application::CalculeFPSHistogram()
{

	for (int i = 0; i <HISTOGRAM_LIMIT; i++)
	{
		fps_values[i] = fps_values[i + 1];
	}
	
	fps_values[HISTOGRAM_LIMIT] = prev_last_sec_frame_count;

}

void Application::CalculeMSHistogram()
{
	for (int i = 0; i <HISTOGRAM_LIMIT; i++)
	{
		millisecons_values[i] = millisecons_values[i + 1];
	}
	millisecons_values[HISTOGRAM_LIMIT] = dt*1000;
}

int Application::GenerateRandom()
{
	return random.Int();
}

bool Application::LoadConfigNow()
{
	bool ret = true;
	
	JSONConfig config;
	if (!config.ParseFile("config.json",file_system->GetSettingsFolder()))
	{
		ret = false;
	}

	if (ret == true)
	{
		JSONConfig app_config=config.SetFocus("App");
		name = app_config.GetString("name");
		organization = app_config.GetString("organization");
		fps_cap = app_config.GetInt("frame_cap");
		SetFPSCap();
		std::list<Module*>::iterator item = list_modules.begin();
		while (item != list_modules.end() && ret == true)
		{
			ret = item._Ptr->_Myval->LoadConfig(config.SetFocus(item._Ptr->_Myval->name.c_str()));
			item++;
		}
	}
	
	return ret;
}

bool Application::SaveConfigNow()
{
	bool ret = true;
	JSONConfig config;
	// Call Awake() in all modules
	if (!config.ParseFile("config.json",file_system->GetSettingsFolder()))
	{
		ret = false;
	}


	if (ret == true)
	{
		JSONConfig app_config = config.SetFocus("App");

		app_config.SetString(name, "name");
		app_config.SetString(organization, "organization");
		app_config.SetInt(fps_cap, "frame_cap");

		std::list<Module*>::iterator item = list_modules.begin();
		while (item != list_modules.end() && ret == true)
		{
			ret = item._Ptr->_Myval->SaveConfig(config.SetFocus(item._Ptr->_Myval->name.c_str()));
			item++;
		}
		config.SerializeFile("config.json");

	}
	
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

update_status Application::GuiUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	if (open_config_window) {
		GuiConfigUpdate();
	}
	if (profiler->CheckWindows()) {
		profiler->DrawProfiler();
	}
	//ImGui::ShowTestWindow();

	//Last
	std::list<Module*>::iterator item = list_modules.begin();
	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{

		profiler->CreateCategory("Application_Update", item._Ptr->_Myval->name.c_str(), "Gui_Update");

		ret = item._Ptr->_Myval->GuiUpdate();
		item++;
	}

	return ret;

	

}

void Application::GuiConfigUpdate()
{

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(550, 600), ImGuiCond_Once);

	if (!ImGui::Begin("Configuration", &open_config_window, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Application"))
	{
		ImGui::InputText("Aplication name", buff, IM_ARRAYSIZE(buff));
		name = buff;

		ImGui::InputText("Organization name", buff2, IM_ARRAYSIZE(buff2));
		organization = buff2;

		ImGui::Text("FPS: %u", frames_on_last_update);
		if (ImGui::SliderInt("Frame Cap", &fps_cap, 0, 120))
		{
			SetFPSCap();
		}
		ImGui::PlotHistogram("FPS Histogram", fps_values, IM_ARRAYSIZE(fps_values), 0, NULL, 0.0f, 120.0f, ImVec2(0, 80));
		ImGui::PlotHistogram("Millisecons Histogram", millisecons_values, IM_ARRAYSIZE(millisecons_values), 0, NULL, 0.0f, 60.0f, ImVec2(0, 80));

		sMStats stats = m_getMemoryStatistics();

		ImGui::Text("Accumulated actual memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.accumulatedActualMemory);
		ImGui::Text("Peak actual memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.peakActualMemory);
		ImGui::Text("Total actual memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.totalActualMemory);
		ImGui::Text("Accumulated allocated memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.accumulatedAllocUnitCount);
		ImGui::Text("Peak actual allocated memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.peakAllocUnitCount);
		ImGui::Text("Total actual allocated memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.totalAllocUnitCount);
		ImGui::Text("Accumulated reported memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.accumulatedReportedMemory);
		ImGui::Text("Peak reported memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.peakReportedMemory);
		ImGui::Text("Total reported memory:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%i", stats.totalReportedMemory);

	}


	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{

		item._Ptr->_Myval->GuiConfigUpdate();
		item++;
	}
	ImGui::Separator();

	if (ImGui::Button("Apply##config_button"))
	{
		SaveConfigNow();
		LoadConfigNow();
	}
	ImGui::SameLine();
	if (ImGui::Button("Discard##config_button"))
	{
		LoadConfigNow();

	}
	ImGui::End();

}
