#pragma once
#include "Globals.h"
class MaterialImporter
{
public:
	MaterialImporter();
	~MaterialImporter();

	bool Init();

	int ImportTexture(const char* filename);
	void SaveTexture(const char * name, char*buffer, int buffer_size);

	void CreateCheckMateTexture();
	bool CleanUp();
	const uint GetCheckID();
private:
	uint checkID;
};

