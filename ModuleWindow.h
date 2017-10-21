#pragma once

#include "Module.h"
#include "SDL/include/SDL.h"
#define WINDOWS_OPTIONS 4
class Application;

struct WindowSize 
{
	WindowSize():width(0),height(0)
	{

	}

public:
	int width = 0;
	int height = 0;
};

class ModuleWindow : public Module
{
public:

	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Awake(const JSON_Object * data);

	void GuiConfigUpdate();
	bool SaveConfig(const JSON_Object * data);
	bool LoadConfig(const JSON_Object * data);
	bool CleanUp();

	void SetTitle(const char* title);
	const char* GetTitle();
	SDL_Window * GetActualWindow();
	const int GetWidth();
	const int GetHeight();
private:
	void SetWindowsFlags(Uint32& flags);
	void  SetWindowSize();
	
public:
	//The window we'll be rendering to
	SDL_Window* window;
	SDL_GLContext glcontext;
	//The surface contained by the window
	SDL_Surface* screen_surface;
private:
	char buff[128] = "Name";
	int width=0;
	int height=0;
	WindowSize window_s[4];
	std::string title; 
	bool windows_options[WINDOWS_OPTIONS] = { false,false,false,false };
	bool windows_size_options[WINDOWS_OPTIONS] = { false,false,false,false };
	bool full_screen = false;
	bool window_full_screen = false;
	bool window_borderless = false;
	bool window_resizable = false;
};

