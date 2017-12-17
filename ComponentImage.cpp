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
	if (config.GetInt("ResourceType") != 0)
	{

		image = (ResourceTexture*)App->resource_manager->Get(config.GetInt("Resource UID"));
		if (image != nullptr)
		{
			image->LoadInMemory();
			tmp_id = image->GetID();
		}
		else
		{
			LOG("Error On LoadComponent: Texture is null");
		}
	}
	enable = config.GetBool("Enable");
	return true;
}

void ComponentImage::ChangeImage(uint ID)
{
	if(ID == 0)
	{ 
		tmp_id = (image != nullptr) ? image->GetID() : 0;
	}
	else
	{
		tmp_id = ID;
	}
	
}

void ComponentImage::InspectorUpdate()
{
	uint flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CheckBox;
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), flags, &enable);
	if (ImGui::BeginPopupContextItem("go_options"))
	{	
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
			
				ImGui::Image((GLuint*)image->GetID(), ImVec2(TEXTURE_SIZE, TEXTURE_SIZE), ImVec2(uv0.x, uv0.y), ImVec2(uv1.x, uv1.y), *(ImVec4*)&image->GetRGBA());

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Image((GLuint*)image->GetID(), ImVec2(TEXTURE_SIZE_HOVER, TEXTURE_SIZE_HOVER), ImVec2(uv0.x, uv0.y), ImVec2(uv1.x, uv1.y), *(ImVec4*)&image->GetRGBA());
					ImGui::EndTooltip();
				}

				ImGui::Text("Texture Path:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", image->GetOrignalName().c_str());
				ImGui::PushItemWidth(200);
				ImGui::Text("Image RGBA");
				ImGui::ColorEdit4("##image_rgba", image->GetRGBA().ptr());
				if (ImGui::DragFloat2("World_UV0##uv_0", &world_uv0.x, 1.0f))
					EqualizeUv();
				if (ImGui::DragFloat2("World_UV1##uv_1", &world_uv1.x, 1.0f))
					EqualizeUv();
				if (ImGui::DragFloat2("UV0##uv_0", &uv0.x, 0.01f))
					EqualizeWorldUv();
				if (ImGui::DragFloat2("UV1##uv_1", &uv1.x, 0.01f))
					EqualizeWorldUv();

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
				SetWorldUvValues();
				tmp_id = image->GetID();
			}
			show_mesh_renderer_window = false;
			ImGui::CloseCurrentPopup();
		}
	}
}


const ResourceTexture * ComponentImage::GetImage() const
{
	return image;
}

void ComponentImage::EqualizeUv()
{
	uv0.x = world_uv0.x / image->GetWidth();
	uv0.y = world_uv0.y / image->GetHeight();
	uv1.x = world_uv1.x / image->GetWidth();
	uv1.y = world_uv1.y / image->GetHeight();



}

void ComponentImage::EqualizeWorldUv()
{
	world_uv0.x =  uv0.x * image->GetWidth();
	world_uv0.y =  uv0.y* image->GetHeight();
	world_uv1.x = uv1.x* image->GetWidth();
	world_uv1.y = uv1.y* image->GetHeight();
}

void ComponentImage::SetWorldUvValues()
{
	world_uv1.x = image->GetWidth();
	world_uv1.y = image->GetHeight();

}

uint ComponentImage::GetImageID() const
{
	return (image!=nullptr)?tmp_id:-1;
}

float2 ComponentImage::GetUV0() const
{
	return uv0;
}
float2 ComponentImage::GetUV1() const
{
	return uv1;
}
