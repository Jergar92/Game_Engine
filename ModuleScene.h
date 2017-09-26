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

private:

public:


private:

};
