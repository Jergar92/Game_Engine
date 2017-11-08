#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "GameObject.h"
#include "ModuleRenderer3D.h"
#include "ComponentMeshRenderer.h"
#include "ModuleScene.h"
#include "Application.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"
#include "Glew\include\GL\glew.h"
#include "imgui\imgui.h"
#include <math.h>

#define NUM_EDGES 12
#define DEFAULT_WITH 16.f
#define DEFAULT_HEITH 9.f

ComponentCamera::ComponentCamera(GameObject* my_go):Component(my_go)
{
	component_name = "Camera";
	type = CAMERA;

	camera_frustrum.nearPlaneDistance = 0.2f;
	camera_frustrum.farPlaneDistance = 200.0f;

	camera_frustrum.type = PerspectiveFrustum;
	camera_frustrum.front = {0,0,1};
	camera_frustrum.up = { 0,1,0 };

	camera_frustrum.pos = {0,0,-5};
	camera_frustrum.verticalFov = vertical_fov;
	SetAspectRatio();

	camera_frustrum.horizontalFov = atan(GetAspectRatio()*tan(camera_frustrum.verticalFov / 2)) * 2;
	UpdateMatrix();
	if (my_go != nullptr)
	{
		OnUpdateMatrix(my_go->GetGlobalMatrix());
	}
}

ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::ObjectInside()
{
	return false;
}

void ComponentCamera::Update(float dt)
{
	DebugDraw();
	Culling();
}

void ComponentCamera::OnUpdateMatrix(const float4x4 & matrix)
{
	camera_frustrum.pos = matrix.TranslatePart();
	camera_frustrum.front = matrix.WorldZ().Normalized();
	camera_frustrum.up = matrix.WorldY().Normalized();
	UpdateMatrix();
}

void ComponentCamera::Culling()
{
	scene = SetElementsOnScene();
	CheckForMesh(scene);

}

GameObject* ComponentCamera::SetElementsOnScene()
{
	return App->scene->GetScene();
}

void ComponentCamera::CheckForMesh(GameObject * scene_go)
{
		if (scene_go != nullptr)
		{
			ComponentMesh* mesh = (ComponentMesh*)scene_go->FindComponent(MESH);
			if (mesh != nullptr)
			{
			
				if (camera_frustrum.Contains(mesh->my_go->GetBoundingBoxAABB()) || camera_frustrum.Contains(mesh->my_go->GetBoundingBoxOBB()))
				{
					mesh->DrawMesh(true);
				}
				else
				{
					if (!enable_culling)
					{
						mesh->DrawMesh(true);
					}
					else
					{
						mesh->DrawMesh(false);
					}
					
				}
			
				
			}
			for (int i = 0; i < scene_go->childs.size(); i++)
			{
				GameObject * tmp = scene_go->childs[i];
				CheckForMesh(tmp);
			}
		}
	
	
}


void ComponentCamera::InspectorUpdate()
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
			ImGui::Checkbox("Eanble Culling##show_bb", &enable_culling);
			
			if (ImGui::Checkbox("Set Render Camera##show_bb", &enable_camera_render))
			{
				if (enable_camera_render)
				{
					App->renderer3D->SetCamera(this);
				}
				else
				{
					App->renderer3D->SetCamera(nullptr);
				}
			}
			

			ImGui::NewLine();
			ImGui::TextWrapped("Aspect ratio:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", GetAspectRatio());

			ImGui::DragFloat("Near Distance", &camera_frustrum.nearPlaneDistance, 0.1, 0.0, camera_frustrum.farPlaneDistance);
			
			ImGui::DragFloat("Far Distance", &camera_frustrum.farPlaneDistance, 0.1);

			if (ImGui::DragFloat("Field of View", &camera_frustrum.verticalFov, 0.1, 0.1))
			{
				camera_frustrum.horizontalFov = atan(GetAspectRatio()*tan(camera_frustrum.verticalFov / 2)) * 2;
			}

			UpdateMatrix();

			ImGui::TreePop();
		}
}




void ComponentCamera::DebugDraw()
{
	glBegin(GL_LINES);
	glLineWidth(1.0f);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

	for (uint i = 0; i < NUM_EDGES; i++)
	{
		glVertex3f(camera_frustrum.Edge(i).a.x, camera_frustrum.Edge(i).a.y, camera_frustrum.Edge(i).a.z);
		glVertex3f(camera_frustrum.Edge(i).b.x, camera_frustrum.Edge(i).b.y, camera_frustrum.Edge(i).b.z);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnd();
}

float ComponentCamera::GetNearDistance()const
{
	return camera_frustrum.nearPlaneDistance;
}

float ComponentCamera::GetFardistance()const
{
	return camera_frustrum.farPlaneDistance;
}

float3 ComponentCamera::GetPosition()const
{
	return camera_frustrum.pos;
}

float ComponentCamera::GetAspectRatio()const
{
	
	 return window_aspect_ratio;
}

void ComponentCamera::SetNearDistance(float distance)
{
	camera_frustrum.nearPlaneDistance = distance;
}

void ComponentCamera::SetFarDistance(float distance)
{
	camera_frustrum.farPlaneDistance = distance;
}

void ComponentCamera::SetAspectRatio()
{

	window_aspect_ratio = DEFAULT_WITH / DEFAULT_HEITH;
}

float * ComponentCamera::GetViewMatrix()const
{
	return (float*)view_matrix.v;
}

float * ComponentCamera::GetProjectionMatrix() const
{
	return (float*)projetion_matrix.v;
}

void ComponentCamera::UpdateMatrix()
{
	view_matrix = camera_frustrum.ViewMatrix();

	view_matrix.Transpose();

	projetion_matrix = camera_frustrum.ProjectionMatrix();

	projetion_matrix.Transpose();

	matrix_update = true;
}

bool ComponentCamera::SaveComponent(JSONConfig & config) const
{
	bool ret = true;
	config.SetInt(type, "Type");
	config.SetBool(my_go->GetUID(), "GameObject UID");
	config.SetBool(enable, "Enable");
	//Save pos,up,front
	config.SetFloat(vertical_fov, "Vertical FOV");
	config.SetFloat(window_aspect_ratio, "Windows aspect ratio");

	return ret;
}

void ComponentCamera::Look(const float3& position)
{
	float3 vector = position - camera_frustrum.pos;

	float3x3 matrix = float3x3::LookAt(camera_frustrum.front, vector.Normalized(), camera_frustrum.up, float3::unitY);

	camera_frustrum.front = matrix.MulDir(camera_frustrum.front).Normalized();
	camera_frustrum.up = matrix.MulDir(camera_frustrum.up).Normalized();
}

