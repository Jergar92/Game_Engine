#pragma once
#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float4.h"

#include "MathGeoLib-1.5\src\Math\float2.h"
#include <string>
#include <vector>
#include "Assimp\include\vector3.h"
#include "Assimp\include\quaternion.h"
#include "Assimp\include\matrix4x4.h"

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
	float4 rgba_color = { 1.0f,1.0f,1.0f,1.0f };

};
struct aiNode;

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<uint> indices,std::vector<Texture> textures);

	~Mesh();

	void SetupMesh();
	void Draw();
	void OnGuiDraw();
	void CleanUp();

	//SetFunctions 
	void SetTransformation(aiMatrix4x4 matrix);
	void SetName(const char* set_name);

	void SetTriangles(uint set_triangles);
	//GetFunctions
	const char* GetName();
	const aiVector3D GetPosition();
	const aiQuaternion GetRotation();
	const aiVector3D GetScale();

private:
public:
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	std::vector<Texture> textures;


private:
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	std::string name;
	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scale;
	uint triangles;

};



