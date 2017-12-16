#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ComponentCamera.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ModuleScene.h"
#include "ModuleEditorWindows.h"
#include "MathGeoLib-1.5\src\Geometry\Triangle.h"
#include "ResourceMesh.h"
ModuleCamera::ModuleCamera()
{
	name = "Camera";
	camera = new ComponentCamera(nullptr);
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
	
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		enable_left = true;
	}
	else
	{
		enable_left = false;
	}


	if (!ImGui::GetIO().WantCaptureKeyboard && !ImGui::IsMouseHoveringAnyWindow())
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && !enable_left)
		{
			OnClick();
		}

		if (App->renderer3D->GetCamera() == camera)
		{
			MoveMouse();
			MoveKeyBoard(dt);
		}
			
	}
	
		if (show_raycast)
		{
			glBegin(GL_LINES);
			glVertex3f(ray.a.x, ray.a.y, ray.a.z);
			glVertex3f(ray.b.x, ray.b.y, ray.b.z);
			glEnd();
		}
	

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

bool ModuleCamera::GetRaycast() const
{
	return show_raycast;
}

bool ModuleCamera::EnableRaycast()
{
	
	if (!show_raycast)
	{
		return show_raycast = true;
	}
	else
	{
		return show_raycast = false;
	}
}

void ModuleCamera::MoveMouse()
{
	// Check motion for lookat / Orbit cameras
	int motion_x, motion_y;
	motion_x = -App->input->GetMouseXMotion();
	motion_y = App->input->GetMouseYMotion();

	if (enable_left && (motion_x != 0 || motion_y != 0))
	{
		Orbit(motion_x,-motion_y);
	}

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		Rotate(motion_x,motion_y);
	}

	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT && (motion_x != 0 || motion_y != 0))
	{
		float distance = reference.Distance(camera->camera_frustrum.pos);
		float3 Y_add = camera->camera_frustrum.up * motion_y * (distance / 1800);
		float3 X_add = camera->camera_frustrum.WorldRight() * motion_x * (distance / 1800);

		reference += X_add;
		reference += Y_add;

		camera->camera_frustrum.pos = camera->camera_frustrum.pos + X_add + Y_add;
		camera->UpdateMatrix();
	}
	// Mouse wheel for zoom
	int wheel = App->input->GetMouseZ();
	if (wheel != 0)
		Zoom(wheel);


}

void ModuleCamera::MoveKeyBoard(float dt)
{
	float speed = 2.0f;
	new_pos.Set(0, 0, 0);
	
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		speed = speed * 5.0f;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		new_pos += camera->camera_frustrum.front * speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		new_pos -= camera->camera_frustrum.front  * speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		new_pos -= camera->camera_frustrum.WorldRight()  *speed;
	}
		
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		new_pos += camera->camera_frustrum.WorldRight()  * speed;
	}
		
	if (new_pos.LengthSq() > 0.0f)
	{
		camera->camera_frustrum.pos += new_pos * dt;
		reference += new_pos * dt;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		Focus(App->editor_window->GetSelectedGameObject());
	}

	camera->UpdateMatrix();
	
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
	camera->UpdateMatrix();
}

void ModuleCamera::Rotate(float dx, float dy)
{
	if (dx != 0.0f)
	{
		Quat quat_x = Quat::RotateY(0.3*dx*DEGTORAD);
		camera->camera_frustrum.front = quat_x.Transform(camera->camera_frustrum.front).Normalized();
		camera->camera_frustrum.up = quat_x.Transform(camera->camera_frustrum.up).Normalized();

	}

	if (dy != 0.0f)
	{
		Quat quat_y = Quat::RotateAxisAngle(camera->camera_frustrum.WorldRight(), -0.3*dy * DEGTORAD);
		camera->camera_frustrum.up = quat_y.Transform(camera->camera_frustrum.up).Normalized();
		camera->camera_frustrum.front = quat_y.Transform(camera->camera_frustrum.front).Normalized();
		
		float3 new_axis = quat_y.Mul(camera->camera_frustrum.up).Normalized();
		
		if (new_axis.y != 0)
		{
			camera->camera_frustrum.up = new_axis;
			camera->camera_frustrum.front = quat_y.Mul(camera->camera_frustrum.front).Normalized();
		}
	}
	
	float3 distance = reference - camera->camera_frustrum.pos;
	reference = camera->camera_frustrum.pos + (camera->camera_frustrum.front.Normalized() * distance.Length());
	camera->UpdateMatrix();
}

void ModuleCamera::Focus(GameObject* Clicked)
{
	//LookAt(Clicked->position);
}

// -----------------------------------------------------------------
void ModuleCamera::Zoom(float zoom)
{
	float distance = reference.Distance(camera->camera_frustrum.pos);
	float3 newPos = camera->camera_frustrum.pos + camera->camera_frustrum.front * zoom * distance * 0.05f;
	camera->camera_frustrum.pos = newPos;
	camera->UpdateMatrix();
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
	
	ray = camera->camera_frustrum.UnProjectLineSegment(mouseNormX,mouseNormY);
	OnCollision();
}

void ModuleCamera::OnCollision()
{
	GameObject* scene = App->scene->GetScene();
	std::map<float,GameObject*> go;
	
	for (uint i = 0; i < scene->childs.size(); i++)
	{
		GameObjectsChilds(scene->childs[i],go);
	}
	if (go.size() > 0)
	{
		App->editor_window->SetSelectedGameObject(go.begin()->second);
		LOG("GameObject picked: %s", go.begin()->second->name.c_str());
	}
}

void ModuleCamera::GameObjectsChilds(GameObject *go,std::map<float,GameObject*>&my_vector)
{
	LineSegment ray_copy = ray;
	ray_copy.Transform(go->GetGlobalMatrix().Inverted());
	
	if (ray_copy.Intersects(go->GetIdentityBoundingBoxAABB()))
	{
		ComponentMesh* mesh = (ComponentMesh*)go->FindComponent(MESH);
		if (mesh != nullptr)
		{
			if (mesh->HaveResourceMesh())
			{
				std::vector<Vertex> vertices = mesh->GetVertices();
				std::vector<uint> indices = mesh->GetIndices();
				float final_distance = -1;
				for (uint i = 0; i < indices.size(); i += 3)
				{


					float3 v1 = vertices[indices[i]].position;
					float3 v2 = vertices[indices[i + 1]].position;
					float3 v3 = vertices[indices[i + 2]].position;

					Triangle vertex_triangle(v1, v2, v3);
					float3 intersection_point;

					if (ray_copy.Intersects(vertex_triangle, nullptr, &intersection_point))
					{

						float distance = Distance(ray_copy.a, intersection_point);
						if (final_distance == -1)
						{
							final_distance = distance;
						}
						else if (final_distance > distance)
						{
							final_distance = distance;
						}
					}
				}
				if (final_distance != -1)
				{
					my_vector[final_distance] = go;
				}

			}
			
		}
	}
	
	for (uint i = 0; i < go->childs.size(); i++)
	{
		GameObjectsChilds(go->childs[i],my_vector);
	}
}

