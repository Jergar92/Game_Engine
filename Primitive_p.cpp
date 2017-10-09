#include "Application.h"
#include "Globals.h"
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

void Primitive_p::GLAllocateElement(float3 * vertex, int size)
{
	GLuint element_id;

	float3* get_vertex = new float3[size];
	memcpy(get_vertex, vertex, size);
	glGenBuffers(1, &element_id);
	glBindBuffer(GL_ARRAY_BUFFER, element_id);
	glBufferData(GL_ARRAY_BUFFER, size, get_vertex, GL_STATIC_DRAW);
	elements.push_back(new PGeometry(element_id, get_vertex, size));
	delete[] get_vertex;
}

void Primitive_p::DrawElements()
{
	std::list<PGeometry*>::iterator item = elements.begin();
	while (item != elements.end())
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, array_index_id);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_element_size);
		glDrawElements(GL_TRIANGLES, sizeof(GLushort) * 72, GL_UNSIGNED_SHORT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Primitive_p::CreateCube(float3 vertexcube[36],float3 position, int size)

{

	AABB cube1;
   

	float3 size_(size, size, size);

	cube1.SetFromCenterAndSize(position, size_);
cube1.Triangulate(1, 1, 1, vertexcube, NULL, NULL, NULL);

	vertex_array.clear();
	vertex_id.clear();
	index.clear();
	
	GLAllocateElement(vertexcube,size);
	for (int i = 0; i < 36 ; i++)
	{
		vertex_array.push_back(vertexcube[i]);
		IndexConversor();
	}
	DrawElements();
}

PGeometry::PGeometry(GLuint buffer_id, float3 * _vertex, int size):buffer_id(buffer_id), size(size)
{
	vertex = new float3[size];
	memcpy(vertex, _vertex, size);
}

PGeometry::~PGeometry()
{
	delete[] vertex;
}
