#pragma once

#include "Module.h"
#include <list>
#include "SDL_mixer\include\SDL_mixer.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool start_enabled = true);
	~ModuleAudio();
	bool Awake(const JSONConfig& data);

	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	//Volume functions
	void GuiConfigUpdate();
	bool SaveConfig(JSONConfig& data);
	bool LoadConfig(const JSONConfig& data);
	const int GetMusicVolume();
private:
	void ChangeMusicVolume();
	void ChangeFXVolume();

private:

	Mix_Music*			music=NULL;
	int                 music_volume = 0;
	int                 fx_volume = 0;

	int                 audio_driver = 0;
	int                 audio_device = 0;
	int                 captured = 0;
	std::list<Mix_Chunk*>	fx;
};

