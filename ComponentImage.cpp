#include "ComponentImage.h"
#include "Application.h"
#include "ModuleResourceManager.h"
#include "GameObject.h"
#include "ResourceTexture.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imgui/imgui.h"
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128


ComponentImage::ComponentImage(GameObject * my_go):Component(my_go)
{

	component_name = "Image";
	type = CANVAS_IMAGE;

}

ComponentImage::~ComponentImage()
{

}


void ComponentImage::Update(float dt)
{
}

bool ComponentImage::SaveComponent(JSONConfig & config) const
{
	bool ret = true;

	config.SetInt(type, "Type");
	config.SetInt(my_go->GetUID(), "GameObject UID");
	config.SetInt((image != nullptr)? image->GetResourceType():0, "ResourceType");
	if (image != nullptr)
	{
		config.SetInt(image->GetUID(), "Resource UID");
	}

	config.SetBool(enable, "Enable");
	return ret;
}

bool ComponentImage::LoadComponent(const JSONConfig & config)
{
	
	//SetMaterials
	if (config.GetInt("ResourceType") != 0)
	{
		image = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource UID"));
		if (image != nullptr)
		{
			image->LoadInMemory();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	enable = config.GetBool("Enable");
	return true;
}

void ComponentImage::InspectorUpdate()
{
	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);
	if (ImGui::BeginPopupContextItem("go_options"))
	{	
		//Scene GO protection
		if (ImGui::Button("Delete Component"))
		{
			DeleteComponent();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	if (node_open)
	{
		if (image != nullptr)
		{
			
				ImGui::Image((GLuint*)image->GetID(), ImVec2(TEXTURE_SIZE, TEXTURE_SIZE), ImVec2(0, 1), ImVec2(1, 0), *(ImVec4*)&image->GetRGBA());

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Image((GLuint*)image->GetID(), ImVec2(TEXTURE_SIZE_HOVER, TEXTURE_SIZE_HOVER), ImVec2(0, 1), ImVec2(1, 0), *(ImVec4*)&image->GetRGBA());
					ImGui::EndTooltip();
				}

				ImGui::Text("Texture Path:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", image->GetOrignalName().c_str());
				ImGui::PushItemWidth(200);
				ImGui::Text("Image RGBA");
				ImGui::ColorEdit4("##image_rgba", image->GetRGBA().ptr());
			
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
			if (image != nullptr)
			{

				if (new_resource->GetOriginalFile().compare(image->GetOriginalFile()) == 0)
				{
					update = false;
				}
				else
				{
					image->UnLoadInMemory();
					image = (ResourceTexture*)new_resource;

				}
			}
			else
			{
				image = (ResourceTexture*)new_resource;
			}
			if (update)
			{
				image->LoadInMemory();
			}
			show_mesh_renderer_window = false;
			ImGui::CloseCurrentPopup();
		}
	}
}

const Quad ComponentImage::GetImageRect() const
{
	return image_rect;
}

const ResourceTexture * ComponentImage::GetImage() const
{
	return image;
}

Quad::Quad(int pos_x, int pos_y, int width, int height) :pos_x(pos_x), pos_y(pos_y), width(width), height(height)
{
	SetUpVertices();
}

void Quad::SetUpVertices()
{
	vertices[0] = pos_x;
	vertices[1] = pos_y;
	vertices[3] = pos_x;
	vertices[4] = pos_y + height;
	vertices[6] = pos_x + width;
	vertices[7] = pos_y + height;
	vertices[9] = pos_x + width;
	vertices[10] = pos_y;

}