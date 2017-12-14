#pragma once
#include "Globals.h"
#include "Resource.h"
//ImGui define dat
#include <memory>

#include "imgui\stb_truetype.h"
#ifndef STB_TRUETYPE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#endif // !1

struct AtlasQuad
{
	uint EBO = 0;
	uint VBO = 0;
	uint uvBuffer = 0;
	float time = 0;
} ;


class ResourceFont:public Resource
{
public:
	ResourceFont(uint UID);
	~ResourceFont();

	void LoadInMemory();
	void Load();
	void UnLoadInMemory();
	void UnLoad();

	AtlasQuad atlas;
	int size = 40;
	uint atlas_width = 1024;
	uint atlas_height = 1024;
	uint oversample_x = 2;
	uint oversample_y = 2;
	uint first_char = ' ';
	uint char_count = '~' - ' ';
	std::unique_ptr<stbtt_packedchar[]> char_info;

	uint id = 0;
private:

};

