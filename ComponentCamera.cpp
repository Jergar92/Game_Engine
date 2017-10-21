#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui\imgui.h"


ComponentCamera::ComponentCamera(GameObject* my_go):Component(my_go),enable(true)
{
	component_name = "Camera";
	type = CAMERA;

	camera_frustrum.nearPlaneDistance = 15.f;
	camera_frustrum.farPlaneDistance = 30.f;

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
	GetAspectRatio();
}


void ComponentCamera::InspectorUpdate()
{
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	if (node_open)
	{

		ImGui::TreePop();

	}

	if(enable == true)
	{
		ImGui::TextWrapped("Aspect ratio:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", GetAspectRatio());


		ImGui::DragFloat("Near Distance", &camera_frustrum.nearPlaneDistance, 0.1, 0.0, camera_frustrum.farPlaneDistance);

		ImGui::DragFloat("Far Distance", &camera_frustrum.farPlaneDistance, 0.1);


		static int selected_option = 0;
		if (ImGui::Combo("Perspective type", &selected_option, "Perspective\0Orthographic", 2))
		{
			if (selected_option == 0)
				camera_frustrum.type = PerspectiveFrustum;
			else if (selected_option == 1)
				camera_frustrum.type = OrthographicFrustum;
		}


		if (ImGui::DragFloat("Field of View", &camera_frustrum.verticalFov, 0.1, 0.1))
		{
			camera_frustrum.horizontalFov = atan(GetAspectRatio()*tan(camera_frustrum.verticalFov / 2)) * 2;
		}
	}

}

float ComponentCamera::GetNearDistance()
{
	return camera_frustrum.nearPlaneDistance;
}

float ComponentCamera::GetFardistance()
{
	return camera_frustrum.farPlaneDistance;
}

int ComponentCamera::GetAspectRatio()
{
	 return window_aspect_ratio = App->window->GetWidth() + App->window->GetHeight();
}

void ComponentCamera::SetNearDistance(float distance)
{
	camera_frustrum.nearPlaneDistance = distance;
}

void ComponentCamera::SetFarDistance(float distance)
{
	camera_frustrum.farPlaneDistance = distance;
}
