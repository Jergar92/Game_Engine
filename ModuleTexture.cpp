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

bool ModuleTexture::Start()
{
	bool ret = true;

	return ret;
}

bool ModuleTexture::CleanUp()
{
	return true;
}
