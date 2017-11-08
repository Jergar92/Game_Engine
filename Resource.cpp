#include "Resource.h"
#include "p2Defs.h"




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

void Resource::SetLibraryFile(const char * set, const char * extension)
{
	library_file = FILE_EXTENSION(set, extension);
}

void Resource::SaveResource(JSONConfig & config) const
{
}

void Resource::LoadResource(const JSONConfig & config)
{
}

const std::string Resource::GetOriginalFile() const
{
	return original_file;
}

const std::string Resource::GetLibraryFile() const
{
	return library_file;
}

void Resource::SetOriginalFile(const char * set)
{
	original_file = set;
}

bool Resource::IsLoadInMemory() const
{
	return load_count==0;
}

ResourceType Resource::GetResourceType() const
{
	return type;
}
