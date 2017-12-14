#include "FontImporter.h"
#include "ModuleFileSystem.h"
#include "Application.h"


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
