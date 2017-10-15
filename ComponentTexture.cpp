#include "ComponentTexture.h"
#include "SDL\include\SDL_opengl.h"


ComponentTexture::ComponentTexture()
{
	component_name = "Texture";
}


ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::Update()
{
	for (int i = 0; i < textures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		glColor4f(textures[i].rgba_color.x, textures[i].rgba_color.y, textures[i].rgba_color.z, textures[i].rgba_color.w);

	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ComponentTexture::GuiDraw()
{
}
