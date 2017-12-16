#include "ResourceFont.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL.h"
#include "SDL_ttf\include\SDL_ttf.h"
ResourceFont::ResourceFont(uint UID):Resource(UID, ResourceType::R_FONT)
{
}


ResourceFont::~ResourceFont()
{
}
void ResourceFont::LoadInMemory()
{
	if (IsLoadInMemory())
	{
		Load();
	}
	load_count++;
}

void ResourceFont::Load()
{
	App->importer->LoadFont(this);

}

void ResourceFont::UnLoadInMemory()
{
	if (load_count>0)
		load_count--;
	if (IsLoadInMemory())
	{
		UnLoad();
	}
}

void ResourceFont::UnLoad()
{
	TTF_CloseFont(font);
}

void ResourceFont::SaveResource(JSONConfig & config) const
{
	config.SetInt(type, "Resource Type");
	config.SetInt(UID, "Resource UID");
	config.SetString(creation_time, "File Creation");
	config.SetString(original_file, "Original File");
	config.SetString(library_file, "Library File");
	config.SetString(meta_file, "Meta File");
}

void ResourceFont::LoadResource(const JSONConfig & config)
{
	creation_time = config.GetString("File Creation");
	original_file = config.GetString("Original File");
	library_file = config.GetString("Library File");
	meta_file = config.GetString("Meta File");
}
