#include "Application.h"
#include "p2Defs.h"
#include "mmgr\mmgr.h"

Application::Application()
{

	window = new ModuleWindow();
	input = new ModuleInput();
	audio = new ModuleAudio();
	renderer3D = new ModuleRenderer3D();
	camera = new ModuleCamera3D();
	scene = new ModuleScene();
	console = new ModuleConsole();
	menu_bar = new ModuleMenuBar();
	hardware = new ModuleHardware();
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);

	//console module
	AddModule(console);
	
	//Scene Module
	AddModule(scene);
	AddModule(hardware);

	AddModule(menu_bar);

	
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

bool Application::Awake()
{
	bool ret = true;
	// Call Awake() in all modules

	JSON_Value * config_data = json_parse_file("config.json");
	if (config_data == NULL)
	{
		ret = false;
	}

	if (ret == true)
	{
		open_config_window = false;
		JSON_Object * object_data = json_value_get_object(config_data);
		JSON_Object * application_data = json_object_dotget_object(object_data, "App");
		name = json_object_dotget_string(application_data, "name");
		organization = json_object_dotget_string(application_data, "organization");
		fps_cap = json_object_get_number(application_data, "frame_cap");

		std::list<Module*>::iterator item = list_modules.begin();
		while (item != list_modules.end() && ret == true)
		{
			//BROFILER_CATEGORY("%s Awake", item._Ptr->_Myval->name.c_str(), Profiler::Color::AliceBlue);

			ret = item._Ptr->_Myval->Awake(object_data);
			item++;
		}
	}
	return ret;
}

bool Application::Start()
{
	bool ret = true;
	//BROFILER_CATEGORY("Aplication Init", Profiler::Color::AliceBlue);

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	std::list<Module*>::iterator item = list_modules.begin();

	item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{

		ret = item._Ptr->_Myval->Start();
		item++;
	}
	
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
	profiler.CreateTitle("Application", Title_chain::BACK);

	profiler.CreateCategory("Application", "FinishUpdate");

	static int values_offset = 0;

	static int millisecons_offset = 0;

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		fps_values[values_offset] = prev_last_sec_frame_count;
		values_offset = (values_offset + 1) % IM_ARRAYSIZE(fps_values);	
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32_t last_frame_ms = frame_time.Read();
	frames_on_last_update = prev_last_sec_frame_count;
	millisecons_values[millisecons_offset] = last_frame_ms;
	millisecons_offset = (millisecons_offset + 1) % IM_ARRAYSIZE(fps_values);
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
	profiler.CreateTitle("Application");
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		profiler.CreateTitle(item._Ptr->_Myval->name.c_str(),Title_chain::FRONT);

		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;	
	}

	item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		profiler.CreateTitle(item._Ptr->_Myval->name.c_str());
		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}
	
	if (ret == UPDATE_CONTINUE) {
		ret = GuiUpdate();
	}

	item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		profiler.CreateTitle(item._Ptr->_Myval->name.c_str(), Title_chain::BACK);

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

void Application::LoadConfigWindows()
{
	open_config_window = !open_config_window;
}

void Application::LoadProfilerWindow()
{
	open_profiler_window = !open_profiler_window;

}

bool Application::LoadConfigNow()
{
	bool ret = true;
	JSON_Value * config_data = json_parse_file("config.json");

	if (config_data == NULL)
	{
		ret = false;
	}

	if (ret == true)
	{
		JSON_Object * object_data = json_value_get_object(config_data);
		JSON_Object * application_data = json_object_dotget_object(object_data, "App");
		name = json_object_dotget_string(application_data, "name");
		organization = json_object_dotget_string(application_data, "organization");
		fps_cap = json_object_get_number(application_data, "frame_cap");
		SetFPSCap();
		std::list<Module*>::iterator item = list_modules.begin();
		while (item != list_modules.end() && ret == true)
		{
			ret = item._Ptr->_Myval->LoadConfig(object_data);
			item++;
		}
	}
	return ret;
}

bool Application::SaveConfigNow()
{
	bool ret = true;
	JSON_Value * config_data = json_parse_file("config.json");

	if (config_data == NULL)
	{
		ret = false;
	}

	if (ret == true)
	{
		JSON_Object * object_data = json_value_get_object(config_data);
		JSON_Object* application_data = json_object_dotget_object(object_data, "App");

		json_object_dotset_string(application_data, "name",name.c_str());
		json_object_dotset_string(application_data, "organization",organization.c_str());
		json_object_dotset_number(application_data, "frame_cap",fps_cap);

		std::list<Module*>::iterator item = list_modules.begin();
		while (item != list_modules.end() && ret == true)
		{
			ret = item._Ptr->_Myval->SaveConfig(object_data);
			item++;
		}
		json_serialize_to_file(config_data, "config.json");

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
	if (open_profiler_window) {
		profiler.DrawProfiler();
	}
	ImGui::ShowTestWindow();
	//Last
	std::list<Module*>::iterator item = list_modules.begin();
	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{

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
	ImGui::SetNextWindowSize(ImVec2(550, 800), ImGuiCond_Once);

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
		ImGui::SliderInt("Frame Cap", &fps_cap, 0, 120);
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
