#include "Resource.h"





Resource::Resource(uint UID, ResourceType type):UID(UID),type(type)
{
}

Resource::~Resource()
{
}

uint Resource::GetUID() const
{
	return UID;
}

void Resource::SaveResource(JSONConfig & config) const
{
}

void Resource::LoadResource(const JSONConfig & config)
{
}

bool Resource::IsLoadInMemory() const
{
	return load_count==0;
}

ResourceType Resource::GetResourceType() const
{
	return type;
}
