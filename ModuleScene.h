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
struct PGeometry
{
	PGeometry(GLuint buffer_id, float3* vertex, int size);

	~PGeometry();
	GLuint buffer_id;
	float3* vertex;
	int size;

};
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
	
	void CubeVertexMode();
	void cubeDirectMode();
	void CubeIndexMode();

	void GLAllocateElement(float3* vertex, int size);
	void DrawElements();


	GLuint array_id;
	uint   array_size;
	GLuint array_index_id;
	uint   array_index_size;
	GLuint buffer_element_id;
	uint   buffer_element_size;

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
	std::list<PGeometry*> elements;

public:


private:

};