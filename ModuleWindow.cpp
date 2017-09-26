#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui\imgui_impl_sdl.h"

ModuleWindow::ModuleWindow(bool start_enabled)
{
	name = "Windows";

	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}
// Called before render is available
bool ModuleWindow::Awake(const JSON_Object * data)
{
	//BROFILER_CATEGORY("Module Window Awake", Profiler::Color::AliceBlue);

	LOG("Init SDL window & surface");
	bool ret = true;


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{

		JSON_Object * window_data = json_object_dotget_object(data, name.c_str());
		
		SetWindowSize();
		//Create window
		title = json_object_dotget_string(window_data, "title");
		width = json_object_dotget_number(window_data, "width") * SCREEN_SIZE;
		height = json_object_dotget_number(window_data, "height") * SCREEN_SIZE;
		int i = 0;
		windows_options[i++] = json_object_dotget_boolean(window_data, "full_screen");
		windows_options[i++] = json_object_dotget_boolean(window_data, "window_full_screen");
		windows_options[i++] = json_object_dotget_boolean(window_data, "window_borderless");
		windows_options[i++] = json_object_dotget_boolean(window_data, "window_resizable");


		//Use OpenGL 2.1

		// Setup window
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_DisplayMode current;
		SDL_GetCurrentDisplayMode(0, &current);
		
		Uint32 flags = 0;
		SetWindowsFlags(flags);
		

		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		glcontext = SDL_GL_CreateContext(window);

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			ImGui_ImplSdlGL2_Init(window);
			screen_surface = SDL_GetWindowSurface(window);


		}
	}

	return ret;
}

void ModuleWindow::SetWindowsFlags(Uint32& flags)
{
	int i = 0;
	flags= SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if (windows_options[i++] == true)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	if (windows_options[i++] == true)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	if (windows_options[i++] == true)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}
	if (windows_options[i++] == true)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	}

	
}

void ModuleWindow::GuiUpdate()
{
	//BROFILER_CATEGORY("Module Window GuiUpdate", Profiler::Color::AliceBlue);

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		const char* windows_menu[] = { "Windowed","Full Screen", "Windowed Full Screen", "Borderless", "Window Resizable" };
		static int windows_selected = 0;
		if (ImGui::Combo("Windows Option", &windows_selected, windows_menu, IM_ARRAYSIZE(windows_menu)))
		{
			for (int i = 1;i < IM_ARRAYSIZE(windows_menu);i++)
			{
				windows_options[i-1] = (i == windows_selected) ? true : false;
			}
		}

		const char* windows_size[] = { "1024x600","1152x768","1280x720", "1920x1080" };
		static int windows_size_selected = 0;
		
		if (ImGui::Combo("Windows Size", &windows_size_selected, windows_size, IM_ARRAYSIZE(windows_size)))
		{
			width = window_s[windows_size_selected].width;
			height = window_s[windows_size_selected].height;
			SDL_SetWindowSize(window,width, height);

		}

	}
}

bool ModuleWindow::SaveConfig(const JSON_Object* data)
{
	bool ret = true;
	JSON_Object* window_data = json_object_dotget_object(data, name.c_str());

	json_object_dotset_string(window_data, "title", title.c_str());
	json_object_dotset_number(window_data, "width", width);
	json_object_dotset_number(window_data, "height", height);

	int i = 0;
	json_object_dotset_boolean(window_data, "full_screen", windows_options[i++]);
	json_object_dotset_boolean(window_data, "window_full_screen", windows_options[i++]);
	json_object_dotset_boolean(window_data, "window_borderless", windows_options[i++]);
	json_object_dotset_boolean(window_data, "window_resizable", windows_options[i++]);


	return ret;
}

bool ModuleWindow::LoadConfig(const JSON_Object* data)
{
	bool ret = true;
	JSON_Object * window_data = json_object_dotget_object(data, name.c_str());
	//Create window
	title = json_object_dotget_string(window_data, "title");
	width = json_object_dotget_number(window_data, "width") * SCREEN_SIZE;
	height = json_object_dotget_number(window_data, "height") * SCREEN_SIZE;
	int i = 0;
	windows_options[i++] = json_object_dotget_boolean(window_data, "full_screen");
	windows_options[i++] = json_object_dotget_boolean(window_data, "window_full_screen");
	windows_options[i++] = json_object_dotget_boolean(window_data, "window_borderless");
	windows_options[i++] = json_object_dotget_boolean(window_data, "window_resizable");
	Uint32 flags = 0;
	SetWindowsFlags(flags);
	SDL_SetWindowFullscreen(window, flags);

	return ret;
}
// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		ImGui_ImplSdlGL2_Shutdown();
		SDL_GL_DeleteContext(glcontext);
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

const char * ModuleWindow::GetTitle()
{
	return title.c_str();
}

const int ModuleWindow::GetWidth()
{
	return width;
}

const int ModuleWindow::GetHeight()
{
	return height;
}

void ModuleWindow::SetWindowSize() 
{
	int i = 0;
	window_s[i].width = 1024;
	window_s[i++].height = 600;

	window_s[i].width = 1152;
	window_s[i++].height = 768;

	window_s[i].width = 1280;
	window_s[i++].height = 720;

	window_s[i].width = 1920;
	window_s[i++].height = 1080;
	
}