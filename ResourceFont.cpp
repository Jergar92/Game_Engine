#include "ResourceFont.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "Glew\include\GL\glew.h"

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
	id=App->importer->LoadFont(this);

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
	glDeleteTextures(1, &id);
	id = -1;

}