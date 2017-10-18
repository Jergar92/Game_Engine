#include "Globals.h"
#include "Application.h"
#include "imgui\imgui.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#define MAX_DISTANCE 100.0f
#define MIN_DISTANCE 0.01f
ModuleCamera3D::ModuleCamera3D(bool start_enabled)
{
	name = "Camera";

	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);


}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;


	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{

	if (!ImGui::GetIO().WantCaptureKeyboard && !ImGui::IsMouseHoveringAnyWindow())
	{

		vec3 new_pos(0, 0, 0);
		float speed = 3.0f * dt;

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			enable_right = true;
		}
		else
		{
			enable_right = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT
			&& App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			enable_left = true;
		}
		else
		{
			enable_left = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed = 8.0f * dt;

		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
			new_pos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
			new_pos.y -= speed;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && enable_right == true)
			new_pos -= Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && enable_right == true)
			new_pos += Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && enable_right == true)
			new_pos -= X * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && enable_right == true)
			new_pos += X * speed;

		Position += new_pos;
		Reference += new_pos;
		// Mouse motion ----------------Wheel Zoom
		float wheel_direction = (float)App->input->GetMouseZ();

		Position -= Reference;

		if (wheel_direction < 0 && length(Position) < MAX_DISTANCE)
		{
			Position += Position * 0.1f;
		}

		if (wheel_direction > 0 && length(Position) >MIN_DISTANCE)
		{
			Position -= Position * 0.1f;
		}

		Position += Reference;

		// Mouse motion ----------------Wheel camera X Y position
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				new_pos += (X * speed * DeltaX);
			}
			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				new_pos -= (Y* speed*DeltaY);
			}
			Position += new_pos;
			Reference += new_pos;

		}
		// Mouse motion ----------------Rotate Camera
		if (enable_right || enable_left)
		{
			vec3 new_pos(0, 0, 0);

			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			if (enable_left == true)
				Position -= Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				Y = rotate(Y, DeltaY, X);
				Z = rotate(Z, DeltaY, X);

				if (Y.y < 0.0f)
				{
					Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Y = cross(Z, X);
				}
			}


			if (enable_left == true)
				Position = Reference + Z * length(Position);
			else
			{
				Reference = Position - Z *length(Position);
			}

		}

		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		{

			if (App->scene->GetModel() != nullptr)
			{
				LOG("Focus Mesh");
				App->camera->Focus(App->scene->GetModel()->GetCenter());
			}
		}


	}
	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}
void ModuleCamera3D::MovePosition(const vec3 &Movement)
{
	Position = Movement;

	Position = Reference + Z * length(Position);


	CalculateViewMatrix();
}
//-------------------------------------------------------------------
void ModuleCamera3D::Focus(const vec3 &focus)
{
	//vec3 result;
	//result = focus - Reference;
	//App->scene->GetModel()->GetDistance();
	Reference = focus;
	MovePosition(focus + App->scene->GetModel()->GetDistance());
	LookAt(focus);

}

void ModuleCamera3D::Rotate(float dx, float dy)
{
	float Sensitivity = 0.25f;
	dx = -App->input->GetMouseXMotion();

	if (dx != 0 && dy != 0)
	{
		Position -= Reference;

		if (dx == Reference.x, dy == Reference.y)
		{

			float DeltaX = (float)dx * Sensitivity;
			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));


		}
		Position = Reference + Z * length(Position);
	}
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}