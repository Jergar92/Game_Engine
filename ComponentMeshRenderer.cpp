#include "ComponentMeshRenderer.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ComponentMeshRenderer::ComponentMeshRenderer(GameObject* my_go) :Component(my_go)
{

}


ComponentMeshRenderer::~ComponentMeshRenderer()
{
}

void ComponentMeshRenderer::Update()
{
	if (mesh == nullptr)
		return;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	for (int i = 0; i < textures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		glColor4f(textures[i].rgba_color.x, textures[i].rgba_color.y, textures[i].rgba_color.z, textures[i].rgba_color.w);

	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexBuffer());
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);




	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetElementBuffer());
	glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//Reset TextureColor
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void ComponentMeshRenderer::SetMesh(ComponentMesh * set_mesh)
{
	mesh = set_mesh;
}

void ComponentMeshRenderer::SetTexture(const std::vector<Texture>& texture)
{
	textures = texture;
}
