#pragma once

#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
class Primitive_p
{
public:
	Primitive_p();
	~Primitive_p();

private:
public:
	float3 position;
	float3 rotation;
	float3 scale;

	std::vector<float3> vertex_id;
	std::vector<float3> vertex_buffer;
};

