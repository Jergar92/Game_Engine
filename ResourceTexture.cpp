#include "ResourceTexture.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "Glew\include\GL\glew.h"

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

void ResourceTexture::UnLoadInMemory()
{
	load_count--;
	if (IsLoadInMemory())
	{
		glDeleteTextures(1, &id);
	}
}

void ResourceTexture::SaveResource(JSONConfig & config) const
{
	config.SetInt(type, "Resource Type");
	config.SetInt(UID, "Resource UID");

	config.SetString(original_file, "Original File");
	config.SetString(library_file, "Library File");
	config.SetString(meta_file, "Meta File");

}

void ResourceTexture::LoadResource(const JSONConfig & config)
{


	original_file= config.GetString("Original File");
	library_file = config.GetString("Library File");
	meta_file = config.GetString("Meta File");

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


