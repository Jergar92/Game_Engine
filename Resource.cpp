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

void Resource::Save(JSONConfig & config) const
{
}

void Resource::Load(const JSONConfig & config)
{
}

bool Resource::IsLoadInMemory() const
{
	return load_count==0;
}
