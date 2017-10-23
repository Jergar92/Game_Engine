#include "ComponentCamera.h"
#include "Application.h"
#include "MathGeoLib-1.5\src\MathGeoLib.h"
#include "SDL\include\SDL_opengl.h"
#include "imgui\imgui.h"
#include <math.h>

#define NUM_EDGES 12
ComponentCamera::ComponentCamera(GameObject* my_go):Component(my_go),enable(true)
{
	component_name = "Camera";
	type = CAMERA;

	camera_frustrum.nearPlaneDistance = 0.2f;
	camera_frustrum.farPlaneDistance = 10.0f;

	camera_frustrum.type = PerspectiveFrustum;
	camera_frustrum.front = front;
	camera_frustrum.up = up;

	camera_frustrum.pos = pos;
	camera_frustrum.verticalFov = vertical_fov;
	GetAspectRatio();

	camera_frustrum.horizontalFov = atan(GetAspectRatio()*tan(camera_frustrum.verticalFov / 2)) * 2;
	
}

ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::ObjectInside()
{
	return false;
}

void ComponentCamera::Update()
{
	DebugDraw();
}


void ComponentCamera::InspectorUpdate()
{
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen);
	
	if (node_open)
	{

		ImGui::TreePop();
		
		if (enable == true)
		{
			ImGui::TextWrapped("Aspect ratio:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", GetAspectRatio());

			ImGui::Checkbox("Enabled##enable_active", &enable);

			ImGui::DragFloat("Near Distance", &camera_frustrum.nearPlaneDistance, 0.1, 0.0, camera_frustrum.farPlaneDistance);

			ImGui::DragFloat("Far Distance", &camera_frustrum.farPlaneDistance, 0.1);


			if (ImGui::DragFloat("Field of View", &camera_frustrum.verticalFov, 0.1, 0.1))
			{
				camera_frustrum.horizontalFov = atan(GetAspectRatio()*tan(camera_frustrum.verticalFov / 2)) * 2;
			}
		}

	}

}

void ComponentCamera::DebugDraw()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_LINES);
	glLineWidth(1.0f);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);

	for (uint i = 0; i < NUM_EDGES; i++)
	{
		glVertex3f(camera_frustrum.Edge(i).a.x, camera_frustrum.Edge(i).a.y, camera_frustrum.Edge(i).a.z);
		glVertex3f(camera_frustrum.Edge(i).b.x, camera_frustrum.Edge(i).b.y, camera_frustrum.Edge(i).b.z);
	}

	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

float ComponentCamera::GetNearDistance()
{
	return camera_frustrum.nearPlaneDistance;
}

float ComponentCamera::GetFardistance()
{
	return camera_frustrum.farPlaneDistance;
}

float3 ComponentCamera::GetPosition()
{
	return camera_frustrum.pos;
}

float ComponentCamera::GetAspectRatio()
{
	float w = 16.f;
	float h = 9.f;
	 return window_aspect_ratio = w/h;
}

void ComponentCamera::SetNearDistance(float distance)
{
	camera_frustrum.nearPlaneDistance = distance;
}

void ComponentCamera::SetFarDistance(float distance)
{
	camera_frustrum.farPlaneDistance = distance;
}
