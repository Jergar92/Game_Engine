#pragma once
#include "Globals.h"
class ResourceTexture;
class MaterialImporter
{
public:
	MaterialImporter();
	~MaterialImporter();

	bool Init();

	int ImportTexture(const char* filename,const char* name);
	void SaveTexture(const char * name);
	int LoadTexture(ResourceTexture * r_path);

	void CreateCheckMateTexture();
	bool CleanUp();
	const uint GetCheckID();
private:
	uint checkID;
};

