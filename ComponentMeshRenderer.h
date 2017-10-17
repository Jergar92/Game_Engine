#pragma once
#include "Component.h"
#include "ComponentMesh.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
struct Texture
{
	uint id;
	std::string type;
	std::string path;
	float4 rgba_color;

};
class ComponentMeshRenderer:public Component
{
public:
	ComponentMeshRenderer(GameObject* my_go);
	~ComponentMeshRenderer();
public:
	void Update();
	ComponentMesh* mesh = nullptr;
	void GetTexture(const std::vector<Texture>& texture);
private:
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	std::vector<Texture> textures;

};

