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
#include "Primitive.h"
#include "Model.h"

class ModuleScene : public Module
{
public:
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status GuiUpdate();

	void cubeDirectMode();

	void CubeIndexMode();

	update_status Update(float dt);
	bool CleanUp();

	Plane_p plane;
private:

public:
	void LoadModel(const char* path);
private:
	std::vector<Model*> models;
	GLuint texture;

	GLuint array_index_id;
	uint   array_index_size;
	GLuint buffer_element_id;
	uint   buffer_element_size;

};