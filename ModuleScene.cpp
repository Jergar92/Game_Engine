#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MathGeoLib-1.5\src\Geometry\Plane.h"

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

	ImGui::PushItemWidth(40);
	static float sphere_1_x = 0.0f;
	ImGui::InputFloat("Sphere_1_x", &sphere_1_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float sphere_1_y = 0.0f;
	ImGui::InputFloat("Sphere_1_y", &sphere_1_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float sphere_1_z = 0.0f;
	ImGui::InputFloat("Sphere_1_z", &sphere_1_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float sphere_1_radius = 0.0f;
	ImGui::InputFloat("Sphere_1_radius", &sphere_1_radius, 0, 0, 1);
	//--------------------------------------------
	//------------------AAOO 1----------------
	ImGui::RadioButton("AAOO_1", &element_1, 2);
	ImGui::PushItemWidth(40);
	static float aaoo_1_min_x = 0.0f;
	ImGui::InputFloat("AAOO_1_min_x", &aaoo_1_min_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_1_min_y = 0.0f;
	ImGui::InputFloat("AAOO_1_min_y", &aaoo_1_min_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_1_min_z = 0.0f;
	ImGui::InputFloat("AAOO_1_min_z", &aaoo_1_min_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float  aaoo_1_max_x = 0.0f;
	ImGui::InputFloat("AAOO_1_max_x", &aaoo_1_max_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_1_max_y = 0.0f;
	ImGui::InputFloat("AAOO_1_max_y", &aaoo_1_max_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_1_max_z = 0.0f;
	ImGui::InputFloat("AAOO_1_max_z", &aaoo_1_max_z, 0, 0, 1);
	//--------------------------------------
	//------------------OBB_1----------------
	ImGui::RadioButton("OBB_1", &element_1, 3);
	ImGui::PushItemWidth(40);
	static float obb_1_min_x = 0.0f;
	ImGui::InputFloat("OBB_1_min_x", &obb_1_min_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_1_min_y = 0.0f;
	ImGui::InputFloat("OBB_1_min_y", &obb_1_min_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_1_min_z = 0.0f;
	ImGui::InputFloat("OBB_1_min_z", &obb_1_min_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float  obb_1_max_x = 0.0f;
	ImGui::InputFloat("OBB_1_max_x", &obb_1_max_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_1_max_y = 0.0f;
	ImGui::InputFloat("OBB_1_max_y", &obb_1_max_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_1_max_z = 0.0f;
	ImGui::InputFloat("OBB_1_max_z", &obb_1_max_z, 0, 0, 1);
	//--------------------------------------
	//------------------Planes_1*----------------
	ImGui::RadioButton("Planes_1", &element_1, 4);
	ImGui::PushItemWidth(40);
	static float planes_1_normal_x = 0.0f;
	ImGui::InputFloat("Plane_1_normal_x", &planes_1_normal_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  planes_1_normal_y = 0.0f;
	ImGui::InputFloat("Plane_1_normal_y", &planes_1_normal_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  planes_1_normal_z = 0.0f;
	ImGui::InputFloat("Plane_1_normal_z", &planes_1_normal_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float  planes_1_constant = 0.0f;
	ImGui::InputFloat("Plane_1_constant", &planes_1_constant, 0, 0, 1);

	//-------------------------------------------
	//------------------Ray_1*----------------
	ImGui::RadioButton("Ray_1", &element_1, 5);
	ImGui::PushItemWidth(40);
	static float ray_1_pos_x = 0.0f;
	ImGui::InputFloat("Ray_1_position_x", &ray_1_pos_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  ray_1_pos_y = 0.0f;
	ImGui::InputFloat("Ray_1_position_y", &ray_1_pos_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  ray_1_pos_z = 0.0f;
	ImGui::InputFloat("Ray_1_position_z", &ray_1_pos_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float ray_1_dir_x = 0.0f;
	ImGui::InputFloat("Ray_1_direction_x", &ray_1_dir_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float ray_1_dir_y = 0.0f;
	ImGui::InputFloat("Ray_1_direction_y", &ray_1_dir_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float ray_1_dir_z = 0.0f;
	ImGui::InputFloat("Ray_1_direction_z", &ray_1_dir_z, 0, 0, 1);

	//-------------------------------------------
	//------------------Triangles_1*----------------
	ImGui::RadioButton("Triangles_1", &element_1, 6);
	ImGui::PushItemWidth(40);
	static float triangle_1_pos_a_x = 0.0f;
	ImGui::InputFloat("Triangle_1_position_A_x", &triangle_1_pos_a_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_1_pos_a_y = 0.0f;
	ImGui::InputFloat("Triangle_1_position_A_y", &triangle_1_pos_a_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_1_pos_a_z = 0.0f;
	ImGui::InputFloat("Triangle_1_position_A_z", &triangle_1_pos_a_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float triangle_1_pos_b_x = 0.0f;
	ImGui::InputFloat("Triangle_1_position_B_x", &triangle_1_pos_b_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float triangle_1_pos_b_y = 0.0f;
	ImGui::InputFloat("Triangle_1_position_B_y", &triangle_1_pos_b_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float triangle_1_pos_b_z = 0.0f;
	ImGui::InputFloat("Triangle_1_position_B_z", &triangle_1_pos_b_z, 0, 0, 1);
	ImGui::PushItemWidth(40);
	static float triangle_1_pos_c_x = 0.0f;
	ImGui::InputFloat("Triangle_1_position_C_x", &triangle_1_pos_c_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_1_pos_c_y = 0.0f;
	ImGui::InputFloat("Triangle_1_position_C_y", &triangle_1_pos_c_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_1_pos_c_z = 0.0f;
	ImGui::InputFloat("Triangle_1_position_C_z", &triangle_1_pos_c_z, 0, 0, 1);

	//-------------------------------------------
	ImGui::Separator();


	static int element_2 = 0;
	ImGui::RadioButton("Sphere_2", &element_2, 0);

	ImGui::PushItemWidth(40);
	static float sphere_2_x = 0.0f;
	ImGui::InputFloat("Sphere_2_x", &sphere_2_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float sphere_2_y = 0.0f;
	ImGui::InputFloat("Sphere_2_y", &sphere_2_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float sphere_2_z = 0.0f;
	ImGui::InputFloat("Sphere_2_z", &sphere_2_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float sphere_2_radius = 0.0f;
	ImGui::InputFloat("Sphere_2_radius", &sphere_2_radius, 0, 0, 1);

	//------------------AAOO 2----------------
	ImGui::RadioButton("AAOO_2", &element_2, 2);
	ImGui::PushItemWidth(40);
	static float aaoo_2_min_x = 0.0f;
	ImGui::InputFloat("AAOO_2_min_x", &aaoo_2_min_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_2_min_y = 0.0f;
	ImGui::InputFloat("AAOO_2_min_y", &aaoo_2_min_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_2_min_z = 0.0f;
	ImGui::InputFloat("AAOO_2_min_z", &aaoo_2_min_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float  aaoo_2_max_x = 0.0f;
	ImGui::InputFloat("AAOO_2_max_x", &aaoo_2_max_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_2_max_y = 0.0f;
	ImGui::InputFloat("AAOO_2_max_y", &aaoo_2_max_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  aaoo_2_max_z = 0.0f;
	ImGui::InputFloat("AAOO_2_max_z", &aaoo_2_max_z, 0, 0, 1);
	//--------------------------------------
	//------------------OBB_2----------------
	ImGui::RadioButton("OBB_2", &element_2, 3);
	ImGui::PushItemWidth(40);
	static float obb_2_min_x = 0.0f;
	ImGui::InputFloat("OBB_2_min_x", &obb_2_min_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_2_min_y = 0.0f;
	ImGui::InputFloat("OBB_2_min_y", &obb_2_min_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_2_min_z = 0.0f;
	ImGui::InputFloat("OBB_2_min_z", &obb_2_min_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float  obb_2_max_x = 0.0f;
	ImGui::InputFloat("OBB_2_max_x", &obb_2_max_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_2_max_y = 0.0f;
	ImGui::InputFloat("OBB_2_max_y", &obb_2_max_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  obb_2_max_z = 0.0f;
	ImGui::InputFloat("OBB_2_max_z", &obb_2_max_z, 0, 0, 1);
	//--------------------------------------
	//------------------Planes_2----------------
	ImGui::RadioButton("Planes_2", &element_2, 4);
	ImGui::PushItemWidth(40);
	static float planes_2_normal_x = 0.0f;
	ImGui::InputFloat("Plane_1_normal_x", &planes_2_normal_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  planes_2_normal_y = 0.0f;
	ImGui::InputFloat("Plane_2_normal_y", &planes_2_normal_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  planes_2_normal_z = 0.0f;
	ImGui::InputFloat("Plane_2_normal_z", &planes_2_normal_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float  planes_2_constant = 0.0f;
	ImGui::InputFloat("Plane_2_constant", &planes_2_constant, 0, 0, 1);

	//-------------------------------------------
	//------------------Ray_2----------------
	ImGui::RadioButton("Ray_2", &element_2, 5);
	ImGui::PushItemWidth(40);
	static float ray_2_pos_x = 0.0f;
	ImGui::InputFloat("Ray_2_position_x", &ray_2_pos_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  ray_2_pos_y = 0.0f;
	ImGui::InputFloat("Ray_2_position_y", &ray_2_pos_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  ray_2_pos_z = 0.0f;
	ImGui::InputFloat("Ray_2_position_z", &ray_2_pos_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float ray_2_dir_x = 0.0f;
	ImGui::InputFloat("Ray_2_direction_x", &ray_2_dir_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float ray_2_dir_y = 0.0f;
	ImGui::InputFloat("Ray_2_direction_y", &ray_2_dir_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float ray_2_dir_z = 0.0f;
	ImGui::InputFloat("Ray_2_direction_z", &ray_2_dir_z, 0, 0, 1);

	//-------------------------------------------
	//------------------Triangles_2----------------
	ImGui::RadioButton("Triangles_2", &element_2, 6);
	ImGui::PushItemWidth(40);
	static float triangle_2_pos_a_x = 0.0f;
	ImGui::InputFloat("Triangle_2_position_A_x", &triangle_2_pos_a_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_2_pos_a_y = 0.0f;
	ImGui::InputFloat("Triangle_2_position_A_y", &triangle_2_pos_a_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_2_pos_a_z = 0.0f;
	ImGui::InputFloat("Triangle_2_position_A_z", &triangle_2_pos_a_z, 0, 0, 1);

	ImGui::PushItemWidth(40);
	static float triangle_2_pos_b_x = 0.0f;
	ImGui::InputFloat("Triangle_2_position_B_x", &triangle_2_pos_b_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float triangle_2_pos_b_y = 0.0f;
	ImGui::InputFloat("Triangle_2_position_B_y", &triangle_2_pos_b_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float triangle_2_pos_b_z = 0.0f;
	ImGui::InputFloat("Triangle_2_position_B_z", &triangle_2_pos_b_z, 0, 0, 1);
	ImGui::PushItemWidth(40);
	static float triangle_2_pos_c_x = 0.0f;
	ImGui::InputFloat("Triangle_2_position_C_x", &triangle_2_pos_c_x, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_2_pos_c_y = 0.0f;
	ImGui::InputFloat("Triangle_2_position_C_y", &triangle_2_pos_c_y, 0, 0, 1); ImGui::SameLine();

	ImGui::PushItemWidth(40);
	static float  triangle_2_pos_c_z = 0.0f;
	ImGui::InputFloat("Triangle_2_position_C_z", &triangle_2_pos_c_z, 0, 0, 1);
	ImGui::Separator();

	//-------------------------------------------
	if (ImGui::Button("Test Colisiion"))
	{

	}


	ImGui::End();
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
