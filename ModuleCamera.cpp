#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ComponentCamera.h"


ModuleCamera::ModuleCamera()
{
	camera = new ComponentCamera(nullptr);

	camera->camera_frustrum.nearPlaneDistance = 0.2f;
	camera->camera_frustrum.farPlaneDistance = 10.0f;
	camera->camera_frustrum.type = PerspectiveFrustum;
	camera->camera_frustrum.pos = float3(10, 100, 0);
	camera->camera_frustrum.front = float3::unitZ;
	camera->camera_frustrum.up = float3::unitY;
	LookAt(float3(0, 0, 0));
	
}


ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Start()
{
	bool ret = true;

	return ret;
}


bool ModuleCamera::CleanUp()
{
	LOG("Cleaning camera");
	delete camera;
	return true;
}

update_status ModuleCamera::Update(float dt)
{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			OnClick();
		}
		
		Move_Mouse();
	
	return UPDATE_CONTINUE;
}


float3 ModuleCamera::GetPosition() const
{
	return camera->camera_frustrum.pos;
}

float3 ModuleCamera::GetReference() const
{
	return reference;
}

// -----------------------------------------------------------------
void ModuleCamera::LookAt(const float3& position)
{
	camera->Look(position);
	reference = position;
}


void ModuleCamera::SetPosition(float3 position)
{
	float3 difference = position - camera->camera_frustrum.pos;
    camera->camera_frustrum.pos = position;
	reference += difference;
}

// -----------------------------------------------------------------
ComponentCamera * ModuleCamera::GetCamera() const
{
	return camera;
}


void ModuleCamera::Move_Mouse()
{
	// Check motion for lookat / Orbit cameras
	int motion_x, motion_y;
	motion_x = -App->input->GetMouseXMotion();
	motion_y = App->input->GetMouseYMotion();

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT && (motion_x != 0 || motion_y != 0))
	{
		Orbit(motion_x, -motion_y);
		
	}

	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT && (motion_x != 0 || motion_y != 0))
	{
		//TODO: Kind of magic number. Consider other options?
		float distance = reference.Distance(camera->camera_frustrum.pos);
		float3 Y_add = camera->camera_frustrum.up * motion_y * (distance / 1800);
		float3 X_add = camera->camera_frustrum.WorldRight() * motion_x * (distance / 1800);

		reference += X_add;
		reference += Y_add;

		camera->camera_frustrum.pos = camera->camera_frustrum.pos + X_add + Y_add;
	}
	// Mouse wheel for zoom
	int wheel = App->input->GetMouseZ();
	if (wheel != 0)
		Zoom(wheel);
}

// -----------------------------------------------------------------
void ModuleCamera::Orbit(float dx, float dy)
{

	float3 vector = camera->camera_frustrum.pos - reference;

	Quat quat_y(camera->camera_frustrum.up, dx * 0.003);
	Quat quat_x(camera->camera_frustrum.WorldRight(), dy * 0.003);

	vector = quat_x.Transform(vector);
	vector = quat_y.Transform(vector);

	camera->camera_frustrum.pos = vector + reference;
	LookAt(reference);
}

// -----------------------------------------------------------------
void ModuleCamera::Zoom(float zoom)
{
	float distance = reference.Distance(camera->camera_frustrum.pos);
	float3 newPos = camera->camera_frustrum.pos + camera->camera_frustrum.front * zoom * distance * 0.05f;
	camera->camera_frustrum.pos = newPos;
}

void ModuleCamera::OnClick()
{
	uint mouseX = App->input->GetMouseX();
	uint mouseY = App->input->GetMouseY();

	uint screen_width = App->window->GetWidth();
    uint screen_height = App->window->GetHeight();

	float mouseNormX = (float)App->input->GetMouseX() / (float)App->window->GetWidth();
	float mouseNormY = (float)App->input->GetMouseY() / (float)App->window->GetHeight();

	//Normalizing mouse position in range of -1 / 1, -1, -1 being at the bottom left corner
	mouseNormX = (mouseNormX - 0.5) / 0.5;
	mouseNormY = -((mouseNormY - 0.5) / 0.5);

}