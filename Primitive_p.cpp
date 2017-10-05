#include "Primitive_p.h"

Primitive_p::Primitive_p()
{
}

Primitive_p::~Primitive_p()
{
}

void Primitive_p::IndexConversor()
{

	for (int i = 0; i < vertex_array.size(); i++)
	{
		if (ExistVertex(vertex_array[i]) != true)
		{
			vertex_id.push_back(vertex_array[i]);
		}
	}

	
	for (int i = 0; i < vertex_array.size(); i++)
	{
		index.push_back(PositionArrayId(vertex_array[i]));
	
	}

}

bool Primitive_p::ExistVertex(float3 &checker)
{
	
	for(int i = 0; i < vertex_id.size();i++)
	{
		if (checker.x == vertex_id[i].x &&
			checker.y == vertex_id[i].y &&
			checker.z == vertex_id[i].z)
			return true;		
	}

	return false;

}

unsigned int Primitive_p::PositionArrayId(float3 & checker)
{
	for (int i = 0; i < vertex_id.size(); i++)
	{
		if (checker.x == vertex_id[i].x &&
			checker.y == vertex_id[i].y &&
			checker.z == vertex_id[i].z)
			return i;
	}
	
	return 0;
}


void Primitive_p::CreateCube(/*float3 position, int size*/)

{

	//AABB cube1;
 //   float3 vertex_cube[36] = {};

	//float3 size_(size, size, size);

	//cube1.SetFromCenterAndSize(position, size_);

	//cube1.Triangulate(1, 1, 1, vertex_cube, NULL, NULL, NULL);

	//vertex_array.clear();
	//vertex_id.clear();
	//index.clear();

	//for (int i = 0; i < 36 ; i++)
	//{
	//	vertex_array.push_back(vertex_cube[i]);
	//}

	vertex_array.push_back(float3(1, 0, 1));
	vertex_array.push_back(float3(1, 1, 1));
	vertex_array.push_back(float3(0, 1, 1));
	vertex_array.push_back(float3(1, 0, 1));
	vertex_array.push_back(float3(1, 1, 1));
	vertex_array.push_back(float3(0, 0, 1));

	IndexConversor();

}