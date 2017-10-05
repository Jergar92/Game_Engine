#pragma once

#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"

class Primitive_p
{
public:
	Primitive_p();
	~Primitive_p();

	//Geometry
	void CreateCube(/*float3 position, int size*/);

private:

	void IndexConversor();
	bool ExistVertex(float3 &);
	unsigned int   PositionArrayId(float3 &);



public:
	float3 position;
	float3 rotation;
	float3 scale;

	std::vector<float3> vertex_id; //Buscador
	std::vector<unsigned int> index; //Asignator
	std::vector<float3> vertex_array;


};
