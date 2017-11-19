#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"
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
	//find mesh component
	SetMesh((ComponentMesh*)my_go->FindComponent(ComponentType::MESH));
	type = MESH_RENDER;
}


ComponentMeshRenderer::~ComponentMeshRenderer()
{
}

void ComponentMeshRenderer::Update(float dt)
{
	std::vector<ResourceTexture*>::iterator it = textures.begin();
	while (it != textures.end())
	{
		if((*it)->GetDelete())
		{
			(*it)->UnLoadInMemory();
			it = textures.erase(it);
		}
		else
		{
			it++;
		}	

	}

}



void ComponentMeshRenderer::Draw()
{
	if (mesh == nullptr || !mesh->HaveResourceMesh() || !mesh->isEnable() || !mesh->GetDrawMesh())
		return;
	//Get Transform
	glPushMatrix();
	glMultMatrixf((float*)&my_go->GetTransposedMatrix());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i] != nullptr)
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]->GetID());
			glColor4f(textures[i]->GetRGBA().x, textures[i]->GetRGBA().y, textures[i]->GetRGBA().z, textures[i]->GetRGBA().w);
		}
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

	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	//Pop Matrix
	glPopMatrix();

	mesh->DrawMesh(false);
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
		if (r_text != nullptr)
		{
			r_text->LoadInMemory();
			textures.push_back(r_text);
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	//	text.id=App->importer->LoadTexture(config_item.GetString("Texture Name"), this);
	//	text.name = config_item.GetString("Texture Name");
	//	r_text->SetRGBA(config_item.GetFloat4("RGBA color"));

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
		if (!textures.empty())
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

				ImGui::Text("Texture Path:");
				ImGui::SameLine();
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", textures[i]->GetOrignalName().c_str());
				ImGui::PushItemWidth(200);
				ImGui::Text("Image RGBA");
				ImGui::ColorEdit4("##image_rgba", textures[i]->GetRGBA().ptr());
			}
		}
		if (ImGui::Button("Select Texture"))
		{
			show_mesh_renderer_window = true;
		}
		ImGui::TreePop();
	}
	if (show_mesh_renderer_window)
	{
		uint UID = App->resource_manager->ResourceWindows(R_TEXTURE);
		if (UID == -1)
		{
			show_mesh_renderer_window = false;
		}
		else if (UID != 0)
		{
			Resource* new_resource = App->resource_manager->Get(UID);
			bool update = true;
			if (!textures.empty())
			{

				if (new_resource->GetOriginalFile().compare((*textures.begin())->GetOriginalFile()) == 0)
				{
					update = false;
				}
				else
				{
					(*textures.begin())->UnLoadInMemory();
					(*textures.begin()) = (ResourceTexture*)new_resource;

				}
			}
			else
			{
				textures.push_back((ResourceTexture*)new_resource);

			}
			if (update)
			{
				(*textures.begin())->LoadInMemory();
			}
			show_mesh_renderer_window = false;
			ImGui::CloseCurrentPopup();
		}
	}
}

void ComponentMeshRenderer::CleanUp()
{
	mesh = nullptr;
	for (std::vector<ResourceTexture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		
		(*it)->UnLoadInMemory();
	}
	textures.clear();
}
