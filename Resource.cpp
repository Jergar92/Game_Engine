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

void Resource::SetMetaFile(const char * set)
{
	meta_file = FILE_EXTENSION(set, "meta.json");

}

void Resource::SaveResource(JSONConfig & config) const
{
	config.SetInt(UID, "Resource UID");
}

void Resource::LoadResource(const JSONConfig & config)
{
	UID = config.GetInt("Resource UID");

}

const std::string Resource::GetOriginalFile() const
{
	return original_file;
}

const std::string Resource::GetLibraryFile() const
{
	return library_file;
}

const std::string Resource::GetMetaJsonFile() const
{
	return meta_file;
}

void Resource::SetOriginalFile(const char * set)
{
	original_file = set;
}

bool Resource::IsLoadInMemory() const
{
	return load_count==0;
}

void Resource::LoadInMemory()
{
	
	load_count++;
}

void Resource::UnLoadInMemory()
{
	load_count--;

}

void Resource::InspectorUpdate()
{
}

ResourceType Resource::GetResourceType() const
{
	return type;
}
