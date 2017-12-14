#pragma once
class ResourceFont;
class FontImporter
{
public:
	FontImporter();
	~FontImporter();

	bool ImportFont(const char* path, const char* name);
	int LoadFont(ResourceFont* font);
};

