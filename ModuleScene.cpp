#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleScene::ModuleScene(Application * app, bool start_enabled):Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;

	
	return ret;
}

void ModuleScene::ColisionMenu()
{
	ImGui::Begin("Colision Menu");

	static int element_1 = 0;
	//------------------Sphere_1------------

	ImGui::RadioButton("Sphere_1", &element_1, 0);
	if (element_1 == 0)
	{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_1_x", &sphere_1_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_1_y", &sphere_1_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_1_z", &sphere_1_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_1_radius", &sphere_1_radius, 0, 0, 1);
	}
	//--------------------------------------------
	//------------------AABB 1----------------
	
		ImGui::RadioButton("AABB_1", &element_1, 1);
		if (element_1 == 1)
		{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_1_min_x", &aaoo_1_min_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_1_min_y", &aaoo_1_min_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_1_min_z", &aaoo_1_min_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AAOO_1_max_x", &aaoo_1_max_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_1_max_y", &aaoo_1_max_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_1_max_z", &aaoo_1_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------OBB_1----------------
	
		ImGui::RadioButton("OBB_1", &element_1, 2);
		if (element_1 == 2)
		{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_1_min_x", &obb_1_min_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_1_min_y", &obb_1_min_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_1_min_z", &obb_1_min_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_1_max_x", &obb_1_max_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_1_max_y", &obb_1_max_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_1_max_z", &obb_1_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------Planes_1*----------------
	
		ImGui::RadioButton("Planes_1", &element_1, 3);
		if (element_1 == 3)
		{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_1_normal_x", &planes_1_normal_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_1_normal_y", &planes_1_normal_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_1_normal_z", &planes_1_normal_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_1_constant", &planes_1_constant, 0, 0, 1);
	}

	//-------------------------------------------
	//------------------Ray_1*----------------
	
		ImGui::RadioButton("Ray_1", &element_1, 4);
		if (element_1 == 4)
		{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_1_position_x", &ray_1_pos_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_1_position_y", &ray_1_pos_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_1_position_z", &ray_1_pos_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_1_direction_x", &ray_1_dir_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_1_direction_y", &ray_1_dir_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_1_direction_z", &ray_1_dir_z, 0, 0, 1);
	}

	//-------------------------------------------
	//------------------Triangles_1*----------------
	
		ImGui::RadioButton("Triangles_1", &element_1, 5);
		if (element_1 == 5)
		{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_A_x", &triangle_1_pos_a_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_A_y", &triangle_1_pos_a_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_A_z", &triangle_1_pos_a_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_B_x", &triangle_1_pos_b_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_B_y", &triangle_1_pos_b_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_B_z", &triangle_1_pos_b_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_C_x", &triangle_1_pos_c_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_C_y", &triangle_1_pos_c_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_1_position_C_z", &triangle_1_pos_c_z, 0, 0, 1);
	}
	//-------------------------------------------
	ImGui::Separator();


	static int element_2 = 0;
	ImGui::RadioButton("Sphere_2", &element_2, 0);
	if (element_2 == 0)
	{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_2_x", &sphere_2_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_2_y", &sphere_2_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_2_z", &sphere_2_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Sphere_2_radius", &sphere_2_radius, 0, 0, 1);
	}
	//------------------AAOO 2----------------
	ImGui::RadioButton("AABB_2", &element_2, 1);
	if (element_2 == 1)
	{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_2_min_x", &aaoo_2_min_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_2_min_y", &aaoo_2_min_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_2_min_z", &aaoo_2_min_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_2_max_x", &aaoo_2_max_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_2_max_y", &aaoo_2_max_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("AABB_2_max_z", &aaoo_2_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------OBB_2----------------

	ImGui::RadioButton("OBB_2", &element_2, 2);
	if (element_2 == 2)
	{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_2_min_x", &obb_2_min_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_2_min_y", &obb_2_min_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_2_min_z", &obb_2_min_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_2_max_x", &obb_2_max_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_2_max_y", &obb_2_max_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("OBB_2_max_z", &obb_2_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------Planes_2----------------
	
		ImGui::RadioButton("Planes_2", &element_2, 3);
		if (element_2 == 3)
		{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_1_normal_x", &planes_2_normal_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_2_normal_y", &planes_2_normal_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_2_normal_z", &planes_2_normal_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Plane_2_constant", &planes_2_constant, 0, 0, 1);
	}

	//-------------------------------------------
	//------------------Ray_2----------------
	ImGui::RadioButton("Ray_2", &element_2, 4);
	if (element_2 == 4)
	{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_2_position_x", &ray_2_pos_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_2_position_y", &ray_2_pos_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_2_position_z", &ray_2_pos_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_2_direction_x", &ray_2_dir_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_2_direction_y", &ray_2_dir_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Ray_2_direction_z", &ray_2_dir_z, 0, 0, 1);
	}
	//-------------------------------------------
	//------------------Triangles_2----------------
	ImGui::RadioButton("Triangles_2", &element_2, 5);
	if (element_2 == 5)
	{
		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_A_x", &triangle_2_pos_a_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_A_y", &triangle_2_pos_a_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_A_z", &triangle_2_pos_a_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_B_x", &triangle_2_pos_b_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_B_y", &triangle_2_pos_b_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_B_z", &triangle_2_pos_b_z, 0, 0, 1);

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_C_x", &triangle_2_pos_c_x, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_C_y", &triangle_2_pos_c_y, 0, 0, 1); ImGui::SameLine();

		ImGui::PushItemWidth(40);
		ImGui::InputFloat("Triangle_2_position_C_z", &triangle_2_pos_c_z, 0, 0, 1);
	}
	ImGui::Separator();

	//-------------------------------------------
	if (ImGui::Button("Test Colisiion"))
	{
		StartTestColision(element_1,element_2);
	}


	ImGui::End();
}

void ModuleScene::CreateElement(Sphere& sphere, float3 center, float radius)
{
	sphere = Sphere(center, radius);
}

void ModuleScene::CreateElement(AABB& aabb, float3 min_value, float3 max_value)
{
	aabb = AABB(min_value, max_value);
}

void ModuleScene::CreateElement(OBB& obb, float3 min_value, float3 max_value)
{
	obb = OBB(AABB(min_value, max_value));
}

void ModuleScene::CreateElement(Plane& plane, float3 normal, float constant)
{
	plane = Plane(normal, constant);
}

void ModuleScene::CreateElement(Ray& ray, float3 position, float3 direction)
{
	ray = Ray(position, direction);
}

void ModuleScene::CreateElement(Triangle& triangle, float3 position_a, float3 position_b, float3 position_c)
{
	triangle = Triangle(position_a, position_b, position_c);
}

void ModuleScene::StartTestColision(int element_1, int element_2)
{
	bool ret = false;
	switch (element_1)
	{
	case 0:
	{
		Sphere sphere1;
		CreateElement(sphere1, float3(sphere_1_x, sphere_1_y, sphere_1_z), sphere_1_radius);
		switch (element_2)
		{
		case 0:
		{
			Sphere sphere2;
			CreateElement(sphere2, float3(sphere_2_x, sphere_2_y, sphere_2_z), sphere_2_radius);
			if (sphere1.Intersects(sphere2))
			{

			}
			else
			{

			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			if (sphere1.Intersects(aabb2))
			{

			}
			else
			{

			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			if (sphere1.Intersects(obb2))
			{

			}
			else
			{

			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			if (sphere1.Intersects(plane2))
			{

			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			if (sphere1.Intersects(ray2))
			{

			}
			else
			{

			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			if (sphere1.Intersects(triangle2))
			{

			}
			else
			{

			}

		}
		break;
		default:
			break;
		}
	}
		break;
	case 1:
	{
		AABB aabb1;
		CreateElement(aabb1, float3(aaoo_1_min_x, aaoo_1_min_y, aaoo_1_min_z), float3(aaoo_1_max_x, aaoo_1_max_y, aaoo_1_max_z));
		switch (element_2)
		{
		case 0:
		{
			Sphere sphere2;
			CreateElement(sphere2, float3(sphere_2_x, sphere_2_y, sphere_2_z), sphere_2_radius);
			if (aabb1.Intersects(sphere2))
			{

			}
			else
			{

			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			if (aabb1.Intersects(aabb2))
			{

			}
			else
			{

			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			if (aabb1.Intersects(obb2))
			{

			}
			else
			{

			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			if (aabb1.Intersects(plane2))
			{

			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			if (aabb1.Intersects(ray2))
			{

			}
			else
			{

			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			if (aabb1.Intersects(triangle2))
			{

			}
			else
			{

			}

		}
		break;
		default:
			break;
		}
	}
		break;
	case 2:
	{
		OBB obb1;
		CreateElement(obb1, float3(obb_1_min_x, obb_1_min_y, obb_1_min_z), float3(obb_1_max_x, obb_1_max_y, obb_1_max_z));
		switch (element_2)
		{
		case 0:
		{
			Sphere sphere2;
			CreateElement(sphere2, float3(sphere_2_x, sphere_2_y, sphere_2_z), sphere_2_radius);
			if (obb1.Intersects(sphere2))
			{

			}
			else
			{

			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			if (obb1.Intersects(aabb2))
			{

			}
			else
			{

			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			if (obb1.Intersects(obb2))
			{

			}
			else
			{

			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			if (obb1.Intersects(plane2))
			{

			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			if (obb1.Intersects(ray2))
			{

			}
			else
			{

			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			if (obb1.Intersects(triangle2))
			{

			}
			else
			{

			}

		}
		break;
		default:
			break;
		}
	}
		break;
	case 3:
	{
		Plane plane1;
		CreateElement(plane1, float3(planes_1_normal_x, planes_1_normal_y, planes_1_normal_z), planes_1_constant);
		switch (element_2)
		{
		case 0:
		{
			Sphere sphere2;
			CreateElement(sphere2, float3(sphere_2_x, sphere_2_y, sphere_2_z), sphere_2_radius);
			if (plane1.Intersects(sphere2))
			{

			}
			else
			{

			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			if (plane1.Intersects(aabb2))
			{

			}
			else
			{

			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			if (plane1.Intersects(obb2))
			{

			}
			else
			{

			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			if (plane1.Intersects(plane2))
			{

			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			if (plane1.Intersects(ray2))
			{

			}
			else
			{

			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			if (plane1.Intersects(triangle2))
			{

			}
			else
			{

			}

		}
		break;
		default:
			break;
		}
	}
		break;
	case 4:
	{
		Ray ray1;
		CreateElement(ray1, float3(ray_1_pos_x, ray_1_pos_y, ray_1_pos_z), float3(ray_1_dir_x, ray_1_dir_y, ray_1_dir_z));
		switch (element_2)
		{
		case 0:
		{
			Sphere sphere2;
			CreateElement(sphere2, float3(sphere_2_x, sphere_2_y, sphere_2_z), sphere_2_radius);
			if (ray1.Intersects(sphere2))
			{

			}
			else
			{

			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			if (ray1.Intersects(aabb2))
			{

			}
			else
			{

			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			if (ray1.Intersects(obb2))
			{

			}
			else
			{

			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			if (ray1.Intersects(plane2))
			{

			}

		}
		break;
		case 4:
		{
			

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			if (ray1.Intersects(triangle2))
			{

			}
			else
			{

			}

		}
		break;
		default:
			break;
		}
	}
		break;
	case 5:
	{
		Triangle triangle1;
		CreateElement(triangle1, float3(triangle_1_pos_a_x, triangle_1_pos_a_y, triangle_1_pos_a_z), float3(triangle_1_pos_b_x, triangle_1_pos_b_y, triangle_1_pos_b_z), float3(triangle_1_pos_c_x, triangle_1_pos_c_y, triangle_1_pos_c_z));
		switch (element_2)
		{
		case 0:
		{
			Sphere sphere2;
			CreateElement(sphere2, float3(sphere_2_x, sphere_2_y, sphere_2_z), sphere_2_radius);
			if (triangle1.Intersects(sphere2))
			{

			}
			else
			{

			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			if (triangle1.Intersects(aabb2))
			{

			}
			else
			{

			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			if (triangle1.Intersects(obb2))
			{

			}
			else
			{

			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			if (triangle1.Intersects(plane2))
			{

			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			if (triangle1.Intersects(ray2))
			{

			}
			else
			{

			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			if (triangle1.Intersects(triangle2))
			{

			}
			else
			{

			}

		}
		break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}

update_status ModuleScene::Update(float dt)
{
	ColisionMenu();
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;


	return ret;
}
