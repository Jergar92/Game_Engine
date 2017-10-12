#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include <list>
#include "SDL_mixer\include\SDL_mixer.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool start_enabled = true);
	~ModuleAudio();
	bool Awake(const JSON_Object * data);

	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	//Volume functions
	void GuiConfigUpdate();
	bool SaveConfig(const JSON_Object * data);
	bool LoadConfig(const JSON_Object * data);
	const int GetVolume();

private:

	Mix_Music*			music=NULL;
	int                 volume = 0;
	int                 audio_driver = 0;
	int                 audio_device = 0;
	int                 captured = 0;
	std::list<Mix_Chunk*>	fx;
};

#endif // __ModuleAudio_H__