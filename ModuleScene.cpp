#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleScene::ModuleScene(bool start_enabled)
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
	ImGui::PushItemWidth(40);

	ImGui::RadioButton("Sphere_1", &element_1, 0);
	if (element_1 == 0)
	{
		ImGui::InputFloat("Sphere_1_x", &sphere_1_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Sphere_1_y", &sphere_1_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Sphere_1_z", &sphere_1_z, 0, 0, 1);
		ImGui::InputFloat("Sphere_1_radius", &sphere_1_radius, 0, 0, 1);
	}
	//--------------------------------------------
	//------------------AABB 1----------------
	
		ImGui::RadioButton("AABB_1", &element_1, 1);
		if (element_1 == 1)
		{
		ImGui::InputFloat("AABB_1_min_x", &aaoo_1_min_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_1_min_y", &aaoo_1_min_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_1_min_z", &aaoo_1_min_z, 0, 0, 1);
		ImGui::InputFloat("AAOO_1_max_x", &aaoo_1_max_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_1_max_y", &aaoo_1_max_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_1_max_z", &aaoo_1_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------OBB_1----------------
	
		ImGui::RadioButton("OBB_1", &element_1, 2);
		if (element_1 == 2)
		{
		ImGui::InputFloat("OBB_1_min_x", &obb_1_min_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_1_min_y", &obb_1_min_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_1_min_z", &obb_1_min_z, 0, 0, 1);
		ImGui::InputFloat("OBB_1_max_x", &obb_1_max_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_1_max_y", &obb_1_max_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_1_max_z", &obb_1_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------Planes_1*----------------
	
		ImGui::RadioButton("Planes_1", &element_1, 3);
		if (element_1 == 3)
		{
		ImGui::InputFloat("Plane_1_normal_x", &planes_1_normal_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Plane_1_normal_y", &planes_1_normal_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Plane_1_normal_z", &planes_1_normal_z, 0, 0, 1);
		ImGui::InputFloat("Plane_1_constant", &planes_1_constant, 0, 0, 1);
	}

	//-------------------------------------------
	//------------------Ray_1*----------------
	
		ImGui::RadioButton("Ray_1", &element_1, 4);
		if (element_1 == 4)
		{
		ImGui::InputFloat("Ray_1_position_x", &ray_1_pos_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_1_position_y", &ray_1_pos_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_1_position_z", &ray_1_pos_z, 0, 0, 1);
		ImGui::InputFloat("Ray_1_direction_x", &ray_1_dir_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_1_direction_y", &ray_1_dir_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_1_direction_z", &ray_1_dir_z, 0, 0, 1);
	}

	//-------------------------------------------
	//------------------Triangles_1*----------------
	
		ImGui::RadioButton("Triangles_1", &element_1, 5);
		if (element_1 == 5)
		{
		ImGui::InputFloat("Triangle_1_position_A_x", &triangle_1_pos_a_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_1_position_A_y", &triangle_1_pos_a_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_1_position_A_z", &triangle_1_pos_a_z, 0, 0, 1);
		ImGui::InputFloat("Triangle_1_position_B_x", &triangle_1_pos_b_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_1_position_B_y", &triangle_1_pos_b_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_1_position_B_z", &triangle_1_pos_b_z, 0, 0, 1);
		ImGui::InputFloat("Triangle_1_position_C_x", &triangle_1_pos_c_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_1_position_C_y", &triangle_1_pos_c_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_1_position_C_z", &triangle_1_pos_c_z, 0, 0, 1);
	}
	//-------------------------------------------
	ImGui::Separator();
	static int element_2 = 0;
	ImGui::RadioButton("Sphere_2", &element_2, 0);
	if (element_2 == 0)
	{
		ImGui::InputFloat("Sphere_2_x", &sphere_2_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Sphere_2_y", &sphere_2_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Sphere_2_z", &sphere_2_z, 0, 0, 1);
		ImGui::InputFloat("Sphere_2_radius", &sphere_2_radius, 0, 0, 1);
	}
	//------------------AAOO 2----------------
	ImGui::RadioButton("AABB_2", &element_2, 1);
	if (element_2 == 1)
	{
		ImGui::InputFloat("AABB_2_min_x", &aaoo_2_min_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_2_min_y", &aaoo_2_min_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_2_min_z", &aaoo_2_min_z, 0, 0, 1);
		ImGui::InputFloat("AABB_2_max_x", &aaoo_2_max_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_2_max_y", &aaoo_2_max_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("AABB_2_max_z", &aaoo_2_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------OBB_2----------------

	ImGui::RadioButton("OBB_2", &element_2, 2);
	if (element_2 == 2)
	{
		ImGui::InputFloat("OBB_2_min_x", &obb_2_min_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_2_min_y", &obb_2_min_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_2_min_z", &obb_2_min_z, 0, 0, 1);
		ImGui::InputFloat("OBB_2_max_x", &obb_2_max_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_2_max_y", &obb_2_max_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("OBB_2_max_z", &obb_2_max_z, 0, 0, 1);
	}
	//--------------------------------------
	//------------------Planes_2----------------
	
		ImGui::RadioButton("Planes_2", &element_2, 3);
		if (element_2 == 3)
		{
		ImGui::InputFloat("Plane_1_normal_x", &planes_2_normal_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Plane_2_normal_y", &planes_2_normal_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Plane_2_normal_z", &planes_2_normal_z, 0, 0, 1);
		ImGui::InputFloat("Plane_2_constant", &planes_2_constant, 0, 0, 1);
	}

	//-------------------------------------------
	//------------------Ray_2----------------
	ImGui::RadioButton("Ray_2", &element_2, 4);
	if (element_2 == 4)
	{
		ImGui::InputFloat("Ray_2_position_x", &ray_2_pos_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_2_position_y", &ray_2_pos_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_2_position_z", &ray_2_pos_z, 0, 0, 1);
		ImGui::InputFloat("Ray_2_direction_x", &ray_2_dir_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_2_direction_y", &ray_2_dir_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Ray_2_direction_z", &ray_2_dir_z, 0, 0, 1);
	}
	//-------------------------------------------
	//------------------Triangles_2----------------
	ImGui::RadioButton("Triangles_2", &element_2, 5);
	if (element_2 == 5)
	{
		ImGui::InputFloat("Triangle_2_position_A_x", &triangle_2_pos_a_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_2_position_A_y", &triangle_2_pos_a_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_2_position_A_z", &triangle_2_pos_a_z, 0, 0, 1);
		ImGui::InputFloat("Triangle_2_position_B_x", &triangle_2_pos_b_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_2_position_B_y", &triangle_2_pos_b_y, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_2_position_B_z", &triangle_2_pos_b_z, 0, 0, 1);
		ImGui::InputFloat("Triangle_2_position_C_x", &triangle_2_pos_c_x, 0, 0, 1); ImGui::SameLine();
		ImGui::InputFloat("Triangle_2_position_C_y", &triangle_2_pos_c_y, 0, 0, 1); ImGui::SameLine();
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

void ModuleScene::RandomNumbers()
{
	ImGui::Begin("Random");
	ImGui::PushItemWidth(80);

	static float random_float = 0.0f;
	static int number_a = 0;
	static int number_b = 0;
	static int random_int = 0;

	ImGui::InputFloat("Float Number", &random_float, 0, 0, 3); ImGui::SameLine();

	if (ImGui::Button("Random Float"))
	{

		random_float = Random.Float();
	}

	ImGui::InputInt("numberA", &number_a, 0, 0); ImGui::SameLine();
	ImGui::InputInt("numberB", &number_b, 0, 0); ImGui::SameLine();
	ImGui::InputInt("RandomInt", &random_int, 0, 0);

	if (ImGui::Button("Random int"))
	{

		random_int = Random.Int((number_a <= number_b) ? number_a : number_b, (number_a>number_b) ? number_a : number_b);
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
			LOG("the sphere 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere1.pos.x, sphere1.pos.y, sphere1.pos.z);
			LOG("the sphere 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere2.pos.x, sphere2.pos.y, sphere2.pos.z);
			if (sphere1.Intersects(sphere2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			LOG("the sphere 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere1.pos.x, sphere1.pos.y, sphere1.pos.z);
			LOG("the AABB2(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb2.maxPoint.x, aabb2.maxPoint.y, aabb2.maxPoint.z,aabb2.minPoint.x, aabb2.minPoint.y, aabb2.minPoint.z);
			if (sphere1.Intersects(aabb2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			LOG("the sphere 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere1.pos.x, sphere1.pos.y, sphere1.pos.z);
			LOG("the OBB2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb2.pos.x, obb2.pos.y, obb2.pos.z);
			if (sphere1.Intersects(obb2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			LOG("the sphere 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere1.pos.x, sphere1.pos.y, sphere1.pos.z);
			LOG("the plane 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane2.normal.x, plane2.normal.y, plane2.normal.z,plane2.d);
			if (sphere1.Intersects(plane2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			LOG("the sphere 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere1.pos.x, sphere1.pos.y, sphere1.pos.z);
			LOG("the Ray 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray2.pos.x, ray2.pos.y, ray2.pos.z, ray2.dir.x, ray2.dir.y, ray2.dir.z);
			if (sphere1.Intersects(ray2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			LOG("the sphere 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere1.pos.x, sphere1.pos.y, sphere1.pos.z);
			LOG("the triangle 2(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle2.a.x, triangle2.a.y, triangle2.a.z, triangle2.b.x, triangle2.b.y, triangle2.b.z, triangle2.c.x, triangle2.c.y, triangle2.c.z);
			if (sphere1.Intersects(triangle2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
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
			LOG("the AABB 1(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb1.maxPoint.x, aabb1.maxPoint.y, aabb1.maxPoint.z, aabb1.minPoint.x, aabb1.minPoint.y, aabb1.minPoint.z);
			LOG("the sphere 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere2.pos.x, sphere2.pos.y, sphere2.pos.z);
			if (aabb1.Intersects(sphere2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			LOG("the AABB 1(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb1.maxPoint.x, aabb1.maxPoint.y, aabb1.maxPoint.z, aabb1.minPoint.x, aabb1.minPoint.y, aabb1.minPoint.z);
			LOG("the AABB 2(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb2.maxPoint.x, aabb2.maxPoint.y, aabb2.maxPoint.z, aabb2.minPoint.x, aabb2.minPoint.y, aabb2.minPoint.z);
			if (aabb1.Intersects(aabb2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			LOG("the AABB 1(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb1.maxPoint.x, aabb1.maxPoint.y, aabb1.maxPoint.z, aabb1.minPoint.x, aabb1.minPoint.y, aabb1.minPoint.z);
			LOG("the OBB2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb2.pos.x, obb2.pos.y, obb2.pos.z);
			if (aabb1.Intersects(obb2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			LOG("the AABB 1(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb1.maxPoint.x, aabb1.maxPoint.y, aabb1.maxPoint.z, aabb1.minPoint.x, aabb1.minPoint.y, aabb1.minPoint.z);
			LOG("the plane 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane2.normal.x, plane2.normal.y, plane2.normal.z, plane2.d);
			if (aabb1.Intersects(plane2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			LOG("the AABB 1(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb1.maxPoint.x, aabb1.maxPoint.y, aabb1.maxPoint.z, aabb1.minPoint.x, aabb1.minPoint.y, aabb1.minPoint.z);
			LOG("the Ray 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray2.pos.x, ray2.pos.y, ray2.pos.z, ray2.dir.x, ray2.dir.y, ray2.dir.z);
			if (aabb1.Intersects(ray2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			LOG("the AABB 1(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb1.maxPoint.x, aabb1.maxPoint.y, aabb1.maxPoint.z, aabb1.minPoint.x, aabb1.minPoint.y, aabb1.minPoint.z);
			LOG("the triangle 2(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle2.a.x, triangle2.a.y, triangle2.a.z, triangle2.b.x, triangle2.b.y, triangle2.b.z, triangle2.c.x, triangle2.c.y, triangle2.c.z);
			if (aabb1.Intersects(triangle2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
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
			LOG("the OBB 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb1.pos.x, obb1.pos.y, obb1.pos.z);
			LOG("the sphere 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere2.pos.x, sphere2.pos.y, sphere2.pos.z);
			if (obb1.Intersects(sphere2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			LOG("the OBB 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb1.pos.x, obb1.pos.y, obb1.pos.z);
			LOG("the AABB 2(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb2.maxPoint.x, aabb2.maxPoint.y, aabb2.maxPoint.z, aabb2.minPoint.x, aabb2.minPoint.y, aabb2.minPoint.z);
			if (obb1.Intersects(aabb2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			LOG("the OBB 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb1.pos.x, obb1.pos.y, obb1.pos.z);
			LOG("the OBB2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb2.pos.x, obb2.pos.y, obb2.pos.z);
			if (obb1.Intersects(obb2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			LOG("the OBB 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb1.pos.x, obb1.pos.y, obb1.pos.z);
			LOG("the plane 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane2.normal.x, plane2.normal.y, plane2.normal.z, plane2.d);
			if (obb1.Intersects(plane2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			LOG("the OBB 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb1.pos.x, obb1.pos.y, obb1.pos.z);
			LOG("the Ray 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray2.pos.x, ray2.pos.y, ray2.pos.z, ray2.dir.x, ray2.dir.y, ray2.dir.z);
			if (obb1.Intersects(ray2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			LOG("the OBB 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb1.pos.x, obb1.pos.y, obb1.pos.z);
			LOG("the triangle 2(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle2.a.x, triangle2.a.y, triangle2.a.z, triangle2.b.x, triangle2.b.y, triangle2.b.z, triangle2.c.x, triangle2.c.y, triangle2.c.z);
			if (obb1.Intersects(triangle2))
			{
				LOG("intersect");
			}
			else
			{
				LOG("not intersect");
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
			App->console->AddLog("the plane 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane1.normal.x, plane1.normal.y, plane1.normal.z, plane1.d);
			App->console->AddLog("the sphere 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere2.pos.x, sphere2.pos.y, sphere2.pos.z);
			if (plane1.Intersects(sphere2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			App->console->AddLog("the plane 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane1.normal.x, plane1.normal.y, plane1.normal.z, plane1.d);
			App->console->AddLog("the AABB 2(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb2.maxPoint.x, aabb2.maxPoint.y, aabb2.maxPoint.z, aabb2.minPoint.x, aabb2.minPoint.y, aabb2.minPoint.z);
			if (plane1.Intersects(aabb2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			App->console->AddLog("the plane 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane1.normal.x, plane1.normal.y, plane1.normal.z, plane1.d);
			App->console->AddLog("the OBB2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb2.pos.x, obb2.pos.y, obb2.pos.z);
			if (plane1.Intersects(obb2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			App->console->AddLog("the plane 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane1.normal.x, plane1.normal.y, plane1.normal.z, plane1.d);
			App->console->AddLog("the plane 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane2.normal.x, plane2.normal.y, plane2.normal.z, plane2.d);
			if (plane1.Intersects(plane2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}

		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			App->console->AddLog("the plane 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane1.normal.x, plane1.normal.y, plane1.normal.z, plane1.d);
			App->console->AddLog("the Ray 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray2.pos.x, ray2.pos.y, ray2.pos.z, ray2.dir.x, ray2.dir.y, ray2.dir.z);
			if (plane1.Intersects(ray2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			App->console->AddLog("the plane 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane1.normal.x, plane1.normal.y, plane1.normal.z, plane1.d);
			App->console->AddLog("the triangle 2(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle2.a.x, triangle2.a.y, triangle2.a.z, triangle2.b.x, triangle2.b.y, triangle2.b.z, triangle2.c.x, triangle2.c.y, triangle2.c.z);
			if (plane1.Intersects(triangle2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
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
			App->console->AddLog("the Ray 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray1.pos.x, ray1.pos.y, ray1.pos.z, ray1.dir.x, ray1.dir.y, ray1.dir.z);
			App->console->AddLog("the sphere 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere2.pos.x, sphere2.pos.y, sphere2.pos.z);
			if (ray1.Intersects(sphere2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			App->console->AddLog("the Ray 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray1.pos.x, ray1.pos.y, ray1.pos.z, ray1.dir.x, ray1.dir.y, ray1.dir.z);
			App->console->AddLog("the AABB 2(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb2.maxPoint.x, aabb2.maxPoint.y, aabb2.maxPoint.z, aabb2.minPoint.x, aabb2.minPoint.y, aabb2.minPoint.z);
			if (ray1.Intersects(aabb2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			App->console->AddLog("the Ray 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray1.pos.x, ray1.pos.y, ray1.pos.z, ray1.dir.x, ray1.dir.y, ray1.dir.z);
			App->console->AddLog("the OBB2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb2.pos.x, obb2.pos.y, obb2.pos.z);
			if (ray1.Intersects(obb2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			App->console->AddLog("the Ray 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray1.pos.x, ray1.pos.y, ray1.pos.z, ray1.dir.x, ray1.dir.y, ray1.dir.z);
			App->console->AddLog("the plane 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane2.normal.x, plane2.normal.y, plane2.normal.z, plane2.d);
			if (ray1.Intersects(plane2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}

		}
		break;
		case 4:
		{
			
			App->console->AddLog("this operation, couldn't be posible");
		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			App->console->AddLog("the Ray 1(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray1.pos.x, ray1.pos.y, ray1.pos.z, ray1.dir.x, ray1.dir.y, ray1.dir.z);
			App->console->AddLog("the triangle 2(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle2.a.x, triangle2.a.y, triangle2.a.z, triangle2.b.x, triangle2.b.y, triangle2.b.z, triangle2.c.x, triangle2.c.y, triangle2.c.z);
			if (ray1.Intersects(triangle2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
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
			App->console->AddLog("the triangle 1(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle1.a.x, triangle1.a.y, triangle1.a.z, triangle1.b.x, triangle1.b.y, triangle1.b.z, triangle1.c.x, triangle1.c.y, triangle1.c.z);
			App->console->AddLog("the sphere 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", sphere2.pos.x, sphere2.pos.y, sphere2.pos.z);
			if (triangle1.Intersects(sphere2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 1:
		{
			AABB aabb2;
			CreateElement(aabb2, float3(aaoo_2_min_x, aaoo_2_min_y, aaoo_2_min_z), float3(aaoo_2_max_x, aaoo_2_max_y, aaoo_2_max_z));
			App->console->AddLog("the triangle 1(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle1.a.x, triangle1.a.y, triangle1.a.z, triangle1.b.x, triangle1.b.y, triangle1.b.z, triangle1.c.x, triangle1.c.y, triangle1.c.z);
			App->console->AddLog("the AABB 2(max X = %.2f ,max Y = %.2f , max Z = %.2f ,min X = %.2f ,min Y = %.2f , min Z = %.2f)", aabb2.maxPoint.x, aabb2.maxPoint.y, aabb2.maxPoint.z, aabb2.minPoint.x, aabb2.minPoint.y, aabb2.minPoint.z);
			if (triangle1.Intersects(aabb2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 2:
		{
			OBB obb2;
			CreateElement(obb2, float3(obb_2_min_x, obb_2_min_y, obb_2_min_z), float3(obb_2_max_x, obb_2_max_y, obb_2_max_z));
			App->console->AddLog("the triangle 1(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle1.a.x, triangle1.a.y, triangle1.a.z, triangle1.b.x, triangle1.b.y, triangle1.b.z, triangle1.c.x, triangle1.c.y, triangle1.c.z);
			App->console->AddLog("the OBB2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f)", obb2.pos.x, obb2.pos.y, obb2.pos.z);
			if (triangle1.Intersects(obb2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 3:
		{
			Plane plane2;
			CreateElement(plane2, float3(planes_2_normal_x, planes_2_normal_y, planes_2_normal_z), planes_2_constant);
			App->console->AddLog("the triangle 1(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle1.a.x, triangle1.a.y, triangle1.a.z, triangle1.b.x, triangle1.b.y, triangle1.b.z, triangle1.c.x, triangle1.c.y, triangle1.c.z);
			App->console->AddLog("the plane 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f constant = %.2f)", plane2.normal.x, plane2.normal.y, plane2.normal.z, plane2.d);
			if (triangle1.Intersects(plane2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}
		}
		break;
		case 4:
		{
			Ray ray2;
			CreateElement(ray2, float3(ray_2_pos_x, ray_2_pos_y, ray_2_pos_z), float3(ray_2_dir_x, ray_2_dir_y, ray_2_dir_z));
			App->console->AddLog("the triangle 1(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle1.a.x, triangle1.a.y, triangle1.a.z, triangle1.b.x, triangle1.b.y, triangle1.b.z, triangle1.c.x, triangle1.c.y, triangle1.c.z);
			App->console->AddLog("the Ray 2(pos X = %.2f ,pos Y = %.2f , pos Z = %.2f dir X = %.2f ,dir Y = %.2f , dir Z = %.2f)", ray2.pos.x, ray2.pos.y, ray2.pos.z, ray2.dir.x, ray2.dir.y, ray2.dir.z);
			if (triangle1.Intersects(ray2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
			}

		}
		break;
		case 5:
		{
			Triangle triangle2;
			CreateElement(triangle2, float3(triangle_2_pos_a_x, triangle_2_pos_a_y, triangle_2_pos_a_z), float3(triangle_2_pos_b_x, triangle_2_pos_b_y, triangle_2_pos_b_z), float3(triangle_2_pos_c_x, triangle_2_pos_c_y, triangle_2_pos_c_z));
			App->console->AddLog("the triangle 1(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle1.a.x, triangle1.a.y, triangle1.a.z, triangle1.b.x, triangle1.b.y, triangle1.b.z, triangle1.c.x, triangle1.c.y, triangle1.c.z);
			App->console->AddLog("the triangle 2(pos aX = %.2f ,pos aY = %.2f , pos aZ = %.2f, pos bX = %.2f ,pos bY = %.2f , pos bZ = %.2f, pos cX = %.2f ,pos cY = %.2f , pos cZ = %.2f)", triangle2.a.x, triangle2.a.y, triangle2.a.z, triangle2.b.x, triangle2.b.y, triangle2.b.z, triangle2.c.x, triangle2.c.y, triangle2.c.z);
			if (triangle1.Intersects(triangle2))
			{
				App->console->AddLog("intersect");
			}
			else
			{
				App->console->AddLog("not intersect");
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
	RandomNumbers();
    
	
	if (show_console)
		App->console->Draw("Test Console", &show_console);
	if (ImGui::Button("Test Console"))
		show_console = !show_console;
	


	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	return ret;
}
