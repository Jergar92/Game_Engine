#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\Sphere.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "MathGeoLib-1.5\src\Geometry\OBB.h"
#include "MathGeoLib-1.5\src\Geometry\Plane.h"
#include "MathGeoLib-1.5\src\Geometry\Ray.h"
#include "MathGeoLib-1.5\src\Geometry\Triangle.h"
#include "MathGeoLib-1.5\src\Algorithm\Random\LCG.h"

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	void ColisionMenu();
	void RandomNumbers();
	void CreateElement(Sphere& sphere,float3 center,float radius);
	void CreateElement(AABB& aabb,float3 min_value ,float3 max_value);
	void CreateElement(OBB& obb, float3 min_value, float3 max_value);
	void CreateElement(Plane& plane, float3 normal, float constant);
	void CreateElement(Ray& ray, float3 position, float3 direction);
	void CreateElement(Triangle& triangle, float3 position_a, float3 position_b, float3 position_c);
	void StartTestColision(int element_1, int element_2);
	update_status Update(float dt);
	bool CleanUp();


private:
	
	LCG Random;

		float sphere_1_x = 0.0f;	
		float sphere_1_y = 0.0f;
		float sphere_1_z = 0.0f;
		float sphere_1_radius = 0.0f;

	//--------------------------------------------
	//------------------AABB 1----------------
		float aaoo_1_min_x = 0.0f;	
		float  aaoo_1_min_y = 0.0f;	
		float  aaoo_1_min_z = 0.0f;
		float  aaoo_1_max_x = 0.0f;	
		float  aaoo_1_max_y = 0.0f;
		float  aaoo_1_max_z = 0.0f;
	
	//--------------------------------------
	//------------------OBB_1----------------

		float obb_1_min_x = 0.0f;
		float  obb_1_min_y = 0.0f;
		float  obb_1_min_z = 0.0f;
		float  obb_1_max_x = 0.0f;
		float  obb_1_max_y = 0.0f;
		float  obb_1_max_z = 0.0f;
	
	//--------------------------------------
	//------------------Planes_1*----------------

		float planes_1_normal_x = 0.0f;
		float  planes_1_normal_y = 0.0f;
		float  planes_1_normal_z = 0.0f;
		float  planes_1_constant = 0.0f;
	

	//-------------------------------------------
	//------------------Ray_1*----------------

		float ray_1_pos_x = 0.0f;
		float  ray_1_pos_y = 0.0f;	
		float  ray_1_pos_z = 0.0f;
		float ray_1_dir_x = 0.0f;
		float ray_1_dir_y = 0.0f;
		float ray_1_dir_z = 0.0f;

	//-------------------------------------------
	//------------------Triangles_1*----------------

		float triangle_1_pos_a_x = 0.0f;
		float  triangle_1_pos_a_y = 0.0f;
		float  triangle_1_pos_a_z = 0.0f;
		float triangle_1_pos_b_x = 0.0f;
		 float triangle_1_pos_b_y = 0.0f;
		 float triangle_1_pos_b_z = 0.0f;
		 float triangle_1_pos_c_x = 0.0f;
		 float  triangle_1_pos_c_y = 0.0f;
		 float  triangle_1_pos_c_z = 0.0f;

	//-------------------------------------------
		 float sphere_2_x = 0.0f;
		 float sphere_2_y = 0.0f;	
		 float sphere_2_z = 0.0f;
		 float sphere_2_radius = 0.0f;
	
	//------------------AAOO 2----------------
		 float aaoo_2_min_x = 0.0f;
		 float  aaoo_2_min_y = 0.0f;
		 float  aaoo_2_min_z = 0.0f;
		 float  aaoo_2_max_x = 0.0f;
		 float  aaoo_2_max_y = 0.0f;
		 float  aaoo_2_max_z = 0.0f;
	
	//--------------------------------------
	//------------------OBB_2----------------
		 float  obb_2_min_x = 0.0f;
		 float  obb_2_min_y = 0.0f;
		 float  obb_2_min_z = 0.0f;
		 float  obb_2_max_x = 0.0f;
		 float  obb_2_max_y = 0.0f;
		 float  obb_2_max_z = 0.0f;
	
	//--------------------------------------
	//------------------Planes_2----------------
		 float planes_2_normal_x = 0.0f;
		 float  planes_2_normal_y = 0.0f;
		 float  planes_2_normal_z = 0.0f;
		 float  planes_2_constant = 0.0f;

	//-------------------------------------------
	//------------------Ray_2----------------
		 float ray_2_pos_x = 0.0f;
		 float  ray_2_pos_y = 0.0f;
		 float  ray_2_pos_z = 0.0f;
		 float ray_2_dir_x = 0.0f;
		 float ray_2_dir_y = 0.0f;
		 float ray_2_dir_z = 0.0f;
	
	//-------------------------------------------
	//------------------Triangles_2----------------	
		 float triangle_2_pos_a_x = 0.0f;
		 float  triangle_2_pos_a_y = 0.0f;
		 float  triangle_2_pos_a_z = 0.0f;
		 float triangle_2_pos_b_x = 0.0f;
		 float triangle_2_pos_b_y = 0.0f;
		 float triangle_2_pos_b_z = 0.0f;
		 float triangle_2_pos_c_x = 0.0f;
		 float  triangle_2_pos_c_y = 0.0f;
		 float  triangle_2_pos_c_z = 0.0f;
public:


private:

};
