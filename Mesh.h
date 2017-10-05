#pragma once
#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include <string>
#include <vector>
struct Vertex
{
	float3 position;
	float3 normals;
	float2 tex_coords;
};
struct Texture
{
	uint id;
	std::string type;
	std::string path;

};
class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<uint> indices,std::vector<Texture> textures);

	~Mesh();

	void SetupMesh();
	void Draw();
	
private:
public:
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	std::vector<Texture> textures;
	std::vector<float3> final_vertex_normals;


private:
	uint VAO;//Vertex Array Object 
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	uint Vector_id;//Element Buffer Object
	uint Normal_id;//Element Buffer Object
	uint Cord_id;//Element Buffer Object

};



