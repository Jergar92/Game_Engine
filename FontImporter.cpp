#include "FontImporter.h"
#include "ModuleFileSystem.h"
#include "Application.h"
#include "ResourceFont.h"
#include "Glew\include\GL\glew.h"
#include "imgui\stb_truetype.h"
#include "SDL\include\SDL.h"
#include "SDL_ttf\include\SDL_ttf.h"

FontImporter::FontImporter()
{
}


FontImporter::~FontImporter()
{
}

bool FontImporter::ImportFont(const char * path, const char * name)
{
	char* buffer = nullptr;
	int size =App->file_system->LoadFile(path, &buffer);
	App->file_system->CloneFile(path, App->file_system->GetAssetsFolder());
	
	return App->file_system->CreateOwnFile(name, buffer, size, App->file_system->GetMaterialFolder(), "ttf");
}

int FontImporter::LoadFont(ResourceFont * font)
{
	
	font->font = TTF_OpenFont(font->GetOriginalFile().c_str(), font->size);
	

	return 1;
}
