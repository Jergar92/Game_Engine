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
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Start();

	update_status Update(float dt);
	bool CleanUp();

	Plane_p plane;
	Cube_p cube;
private:
	
	uint buffer_id = 0;
	uint index_id = 4;

	float sphere_x = 0;
	float sphere_y = 0;
	float sphere_z = 0;

	float sphere_radius = 0;

	float cube_pos_x = 0;
	float cube_pos_y = 0;
	float cube_pos_z = 0;

	float cube_size_x = 0;
	float cube_size_y = 0;
	float cube_size_z = 0;
	std::list<Primitive*> elements;
public:


private:

};
