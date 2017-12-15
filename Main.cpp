#include <stdlib.h>
#include "Application.h"
#include "EventSystem.h"
#include "Globals.h"
#include "p2Defs.h"
#include "imgui\imgui.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

//#include "Brofiler\Brofiler.h"
//#pragma comment(lib, "Brofiler/ProfilerCore32.lib")
enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;
EventSystem* EventS = NULL;
int main(int argc, char ** argv)
{
	//LOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		/*BROFILER_FRAME("Main Loop");*/
		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			EventS = new EventSystem();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("-------------- Application Awake --------------");

			if (App->Awake() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}

			LOG("-------------- Application Start --------------");

			if (App->Start() == false)
			{
				LOG("Application Start exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{


			int update_return = App->Update();
			
			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:
		
			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	RELEASE(App);

	LOG("Exiting game bye...\n");
	return main_return;
}