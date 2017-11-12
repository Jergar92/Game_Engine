#include "ComponentMeshRenderer.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ComponentMesh.h"
#include "ResourceTexture.h"
#include "ResourceMesh.h"
#include "ModuleResourceManager.h"
#include "imgui\imgui.h"
#include "MathGeoLib-1.5\src\Math\float4x4.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
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

void ComponentMeshRenderer::Update(float dt)
{
	if (mesh->GetResourceMesh() == nullptr||!mesh->isEnable() || !mesh->GetDrawMesh() )
		return;
	//Get Transform
	glPushMatrix();
	glMultMatrixf((float*)&my_go->GetTransposedMatrix());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	/*
	if (texture != nullptr)
	{

		glBindTexture(GL_TEXTURE_2D, texture->GetUID());
		glColor4f(texture->GetRGBA().x, texture->GetRGBA().y, texture->GetRGBA().z, texture->GetRGBA().w);
	}
	*/
	for (int i = 0; i < textures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]->GetID());
		glColor4f(textures[i]->GetRGBA().x, textures[i]->GetRGBA().y, textures[i]->GetRGBA().z, textures[i]->GetRGBA().w);

	}
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexBuffer());
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	if (mesh->GetIndices().size() != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetElementBuffer());
		glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}



	//Reset TextureColor
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_REPEAT&&mesh->GetDebugNormal())
	{
		DrawVertexNormals();
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_REPEAT&&mesh->GetDebugNormal())
	{
		DrawTriangleNormals();
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	//Pop Matrix
	glPopMatrix();


}

void ComponentMeshRenderer::DrawVertexNormals()
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexNormalID());
	glVertexPointer(3, GL_FLOAT, sizeof(float3), NULL);
	glDrawArrays(GL_LINES, 0, mesh->GetIndices().size() * 2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ComponentMeshRenderer::DrawTriangleNormals()
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetSurfaceNormalID());
	glVertexPointer(3, GL_FLOAT, sizeof(float3), NULL);
	glDrawArrays(GL_LINES, 0, mesh->GetIndices().size() * 2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void ComponentMeshRenderer::SetMesh(ComponentMesh * set_mesh)
{
	mesh = set_mesh;
}

void ComponentMeshRenderer::SetTexture(const std::vector<ResourceTexture*>& texture)
{
	textures = texture;
}

bool ComponentMeshRenderer::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.OpenArray("Textures");
	std::vector<ResourceTexture*>::const_iterator it = textures.begin();
	while (it != textures.end())
	{
		JSONConfig texture_config;
		
		config.SetInt((*it)->GetResourceType(), "ResourceType");
	
		texture_config.SetInt((*it)->GetResourceType(), "ResourceType");
		texture_config.SetInt((*it)->GetUID(), "Resource UID");

		config.CloseArray(texture_config);
		it++;
	}
	config.SetBool(enable, "Enable");
	return ret;
}

bool ComponentMeshRenderer::LoadComponent(const JSONConfig & config)
{


	
	//find mesh component
	SetMesh((ComponentMesh*)my_go->FindComponent(ComponentType::MESH));
	

	//SetMaterials
	uint size = config.GetArraySize("Textures");
	for (int i = 0; i < size; i++)
	{
		JSONConfig config_item = config.SetFocusArray("Textures", i);
		ResourceTexture* r_text=nullptr;

		r_text = (ResourceTexture*)App->resource_manager->Get(config_item.GetInt("Resource UID"));
		if (r_text == nullptr)
		{

		}
		r_text->LoadInMemory();
	//	text.id=App->importer->LoadTexture(config_item.GetString("Texture Name"), this);
	//	text.name = config_item.GetString("Texture Name");
	//	r_text->SetRGBA(config_item.GetFloat4("RGBA color"));

		textures.push_back(r_text);
	}
	enable = config.GetBool("Enable");
	return false;
}

void ComponentMeshRenderer::InspectorUpdate()
{
	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);
	if (ImGui::BeginPopupContextItem("go_options"))
	{	//Scene GO protection

		if (ImGui::Button("Delete Component"))
		{
			DeleteComponent();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	if (node_open)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			ImGui::Image((GLuint*)textures[i]->GetID(), ImVec2(TEXTURE_SIZE, TEXTURE_SIZE), ImVec2(0, 1), ImVec2(1, 0), *(ImVec4*)&textures[i]->GetRGBA());

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Image((GLuint*)textures[i]->GetID(), ImVec2(TEXTURE_SIZE_HOVER, TEXTURE_SIZE_HOVER), ImVec2(0, 1), ImVec2(1, 0), *(ImVec4*)&textures[i]->GetRGBA());
				ImGui::EndTooltip();
			}
			ImGui::PushItemWidth(200);
			ImGui::Text("Image RGBA");
			ImGui::ColorEdit4("##image_rgba", textures[i]->GetRGBA().ptr());
		}
		ImGui::TreePop();

	}
}

void ComponentMeshRenderer::CleanUp()
{
	mesh = nullptr;
	textures.clear();
}
