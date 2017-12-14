#pragma once
class FontImporter
{
public:
	FontImporter();
	~FontImporter();

	bool ImportFont(const char* path, const char* name);

};

