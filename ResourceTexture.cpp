#include "ResourceTexture.h"
#include "Application.h"
#include "ModuleImporter.h"


ResourceTexture::ResourceTexture(uint UID):Resource(UID,ResourceType::R_TEXTURE), rgba_color (float4(1.0f,1.0f,1.0f,1.0f))
{
}


ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::SetID(uint set_id)
{
	id = set_id;
}

void ResourceTexture::LoadInMemory()
{
	if (IsLoadInMemory())
	{
		App->importer->LoadTexture(this);
	}
	load_count++;
}

uint ResourceTexture::GetID() const
{
	return id;
}



float4 ResourceTexture::GetRGBA() const
{
	return rgba_color;
}

void ResourceTexture::SetRGBA(float4 rgba)
{
	rgba_color = rgba;
}


