#pragma once
#include "Globals.h"
#include "Resource.h"
//ImGui define dat

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
struct Font
{
	const uint size = 40;
	const uint atlas_width = 1024;
	const uint atlas_height = 1024;
	const uint oversample_x = 2;
	const uint oversample_y = 2;
	const uint first_char = ' ';
	const uint char_count = '~' - ' ';
	stbtt_packedchar* char_info=nullptr;
	uint texture = 0;
} ;

class ResourceFont:public Resource
{
public:
	ResourceFont(uint UID);
	~ResourceFont();
	Font font;
	AtlasQuad atlas;
};

