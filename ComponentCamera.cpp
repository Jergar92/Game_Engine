#include "ComponentCamera.h"
#include "Application.h"
#include "imgui\imgui.h"


ComponentCamera::ComponentCamera(GameObject* my_go,float near_distance,float far_distance,bool active) :Component(my_go),enable(active)
{
	component_name = "Camera";
	type = CAMERA;

	camera_frustrum.nearPlaneDistance = near_distance;
	camera_frustrum.farPlaneDistance = far_distance;

	camera_frustrum.type = PerspectiveFrustum;
	camera_frustrum.front = front;
	camera_frustrum.up = up;

	camera_frustrum.pos = pos;
	camera_frustrum.verticalFov = vertical_fov;
	
}


ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::ObjectInside()
{
	return false;
}

void ComponentCamera::InspectorUpdate()
{
	bool node_open = ImGui::TreeNodeEx(component_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	if (node_open)
	{

		ImGui::TreePop();

	}

}

int ComponentCamera::GetAspectRatio()
{
	SDL_GetWindowSize();
	return 0;
}
