#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#define WINDOWS_OPTIONS 4
class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Awake(const JSON_Object * data);

	void GuiUpdate();
	bool SaveConfig(const JSON_Object * data);
	bool LoadConfig(const JSON_Object * data);
	bool CleanUp();

	void SetTitle(const char* title);
	const char* GetTitle();
	const int GetWidth();
	const int GetHeight();
private:
	void SetWindowsFlags(Uint32& flags);
	
public:
	//The window we'll be rendering to
	SDL_Window* window;
	SDL_GLContext glcontext;
	//The surface contained by the window
	SDL_Surface* screen_surface;
private:

	int width=0;
	int height=0;
	std::string title;
	bool windows_options[WINDOWS_OPTIONS] = { false,false,false,false };
	bool full_screen = false;
	bool window_full_screen = false;
	bool window_borderless = false;
	bool window_resizable = false;
};

#endif // __ModuleWindow_H__