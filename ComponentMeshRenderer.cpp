#include "ComponentMeshRenderer.h"
#include "ComponentMesh.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui\imgui.h"
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128

ComponentMeshRenderer::ComponentMeshRenderer(GameObject* my_go) :Component(my_go)
{
	component_name = "Mesh Renderer";
	type = MESH_RENDER;
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

void ComponentMeshRenderer::InspectorUpdate()
{
	bool node_open = ImGui::TreeNode(component_name.c_str());

	if (node_open)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			ImGui::Image((GLuint*)textures[i].id, ImVec2(TEXTURE_SIZE, TEXTURE_SIZE), ImVec2(0, 1), ImVec2(1, 0), *(ImVec4*)&textures[i].rgba_color);

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Image((GLuint*)textures[i].id, ImVec2(TEXTURE_SIZE_HOVER, TEXTURE_SIZE_HOVER), ImVec2(0, 1), ImVec2(1, 0), *(ImVec4*)&textures[i].rgba_color);
				ImGui::EndTooltip();
			}
			ImGui::PushItemWidth(200);
			ImGui::Text("Image RGBA");
			//ImGui::InputFloat4("##image_rgba", &textures[i].rgba_color[0],2);
			ImGui::ColorEdit4("##image_rgba", &textures[i].rgba_color.x);
		}
		ImGui::TreePop();

	}
}
