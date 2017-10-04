#include "Application.h"
#include "ModuleTexture.h"
#include "Devil\include\il.h"
#include "Devil\include\ilu.h"
#include "Devil\include\ilut.h"
#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment (lib, "Devil/libx86/ILU.lib")
#pragma comment (lib, "Devil/libx86/ILUT.lib")

ModuleTexture::ModuleTexture(bool start_enabled)
{
	name = "Texture";
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Awake(const JSON_Object * data)
{
	bool ret = true;
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG("DevIL version is different\n");
		ret = false;
	}
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	return ret;
}

int ModuleTexture::LoadTextureFromFile(const char* path)
{
	std::string filename = std::string(path);

	ILuint textureID;
	ilGenImages(1, &textureID);
	ilBindImage(textureID);

	ILenum error=IL_FALSE;

	ILboolean success = ilLoadImage(path);
	if (success)
	{

		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		

		success = ilConvertImage(ImageInfo.Format, IL_UNSIGNED_BYTE);

		// Quit out if we failed the conversion
		if (!success)
		{
			 error = ilGetError();
			 LOG("ERROR on path:%s ERROR String: %s", path,iluErrorString(error))
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 		// Type of texture
			0,								// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,								// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
			GL_UNSIGNED_BYTE,				// Image data type
			ilGetData());					// The actual image data itself

		glGenerateMipmap(GL_TEXTURE_2D);



		ilBindImage(0);
		ilDeleteImage(textureID);
	}
	else
	{
		error = ilGetError();
		LOG("ERROR on path:%s ERROR String: %s", path, iluErrorString(error))
	}
	//ALWAYS delete
	ilDeleteImages(1, &textureID);
	return textureID;
}

bool ModuleTexture::Start()
{
	bool ret = true;

	return ret;
}

bool ModuleTexture::CleanUp()
{


	return true;
}
