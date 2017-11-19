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
void Resource::ToDelete()
{
	to_delete = true;
}
void Resource::ReImport()
{
	
}
void Resource::SetDateOfCreation(const char * set)
{
	
	creation_time = set;
}
void Resource::SetOriginalFile(const char * set)
{
	original_file = set;
}
void Resource::SetOriginalName(const char * set)
{
	original_name = set;
	
}
void Resource::SetOriginalFile(const char * set, const char* extension)
{
	original_file = FILE_EXTENSION(set, extension);
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

const std::string Resource::GetCreationTime() const
{
	return creation_time;
}

const std::string Resource::GetOrignalName() const
{
	return original_name;
}

bool Resource::GetDelete() const
{
	return to_delete;
}


bool Resource::IsLoadInMemory() const
{
	return load_count==0;
}

void Resource::LoadInMemory()
{
	
	load_count++;
}

void Resource::Load()
{
}

void Resource::UnLoadInMemory()
{
	load_count--;

}

void Resource::UnLoad()
{
}

void Resource::InspectorUpdate()
{
}

void Resource::CleanUp()
{
}

ResourceType Resource::GetResourceType() const
{
	return type;
}
