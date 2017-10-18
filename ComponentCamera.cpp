#include "ComponentCamera.h"
#include "imgui\imgui.h"


ComponentCamera::ComponentCamera(GameObject* my_go) :Component(my_go)
{
	component_name = "Camera";
	type = CAMERA;
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
	bool node_open = ImGui::TreeNode(component_name.c_str());

	if (node_open)
	{

		ImGui::TreePop();

	}

}
