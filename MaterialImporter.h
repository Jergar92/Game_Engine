#pragma once
#include "Globals.h"
class MaterialImporter
{
public:
	MaterialImporter();
	~MaterialImporter();

	bool Init();

	int ImportTexture(const char* filename, uint UID);
	void SaveTexture(const char * name, char*buffer, int buffer_size);
	int LoadTexture(const char * name);

	void CreateCheckMateTexture();
	bool CleanUp();
	const uint GetCheckID();
private:
	uint checkID;
};

