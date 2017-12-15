#pragma once
class ResourceFont;
class FontImporter
{
public:
	FontImporter();
	~FontImporter();

	bool ImportFont(const char* path, const char* name);
	void LoadFont(ResourceFont* font);
};

