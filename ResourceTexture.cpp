#include "ResourceTexture.h"



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

uint ResourceTexture::GetUID() const
{
	return id;
}

float4 ResourceTexture::GetRGBA() const
{
	return rgba_color;
}
