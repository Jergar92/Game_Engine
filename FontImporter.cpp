#include "FontImporter.h"
#include "ModuleFileSystem.h"
#include "Application.h"
#include "ResourceFont.h"
#include "Glew\include\GL\glew.h"
#include "imgui\stb_truetype.h"

#include <memory>

FontImporter::FontImporter()
{
}


FontImporter::~FontImporter()
{
}

bool FontImporter::ImportFont(const char * path, const char * name)
{
	char* buffer = nullptr;
	int size =App->file_system->LoadFile(path, &buffer);
	App->file_system->CloneFile(path, App->file_system->GetAssetsFolder());
	
	return App->file_system->CreateOwnFile(name, buffer, size, App->file_system->GetMaterialFolder(), "ttf");
}

int FontImporter::LoadFont(ResourceFont * font)
{
	char* buffer;
	App->file_system->LoadFile(font->GetOriginalFile().c_str(), &buffer);

	
	auto atlasData = std::make_unique<uint8_t[]>(font->atlas_width * font->atlas_height);

	font->char_info = std::make_unique<stbtt_packedchar[]>(font->char_count);

	stbtt_pack_context context;
	if (!stbtt_PackBegin(&context, atlasData.get(), font->atlas_width, font->atlas_height, 0, 1, nullptr))
		return 0;
		
	
	stbtt_PackSetOversampling(&context, font->oversample_x, font->oversample_y);
	if (!stbtt_PackFontRange(&context,(unsigned char*)buffer, 0, font->size, font->char_count, font->char_count, font->char_info.get()))
		return 0;

	stbtt_PackEnd(&context);

	glGenTextures(1, &font->id);
	glBindTexture(GL_TEXTURE_2D, font->id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, font->atlas_width, font->atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, atlasData.get());
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return font->id;
}
