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
#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"

struct PGeometry
{
	PGeometry(GLuint buffer_id, float3* vertex, int size);

	~PGeometry();
	GLuint buffer_id;
	float3* vertex;
	int size;

};

class Primitive_p
{
public:
	Primitive_p();
	~Primitive_p();

	//Geometry
	void CreateCube(float3 vertexcube[36],float3 position, int size);
	void GLAllocateElement(float3 * vertex, int size);
	void DrawElements();

private:

	void IndexConversor();
	bool ExistVertex(float3 &);
	unsigned int   PositionArrayId(float3 &);

public:
	float3 position;
	float3 rotation;
	float3 scale;
	GLuint array_index_id;
	uint   buffer_element_size;

	std::vector<float3> vertex_id; //Buscador
	std::vector<unsigned int> index; //Asignator
	std::vector<float3> vertex_array;

	std::list<PGeometry*> elements;

};
