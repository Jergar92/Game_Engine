#pragma once
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
struct Texture
{
	uint id;
	std::string type;
	std::string path;
	float4 rgba_color;

};
class ComponentMesh;

class ComponentMeshRenderer:public Component
{
public:
	ComponentMeshRenderer(GameObject* my_go);
	~ComponentMeshRenderer();
public:
	void Update();
	ComponentMesh* mesh = nullptr;
	void SetMesh(ComponentMesh* set_mesh);
	void SetTexture(const std::vector<Texture>& texture);
	void InspectorUpdate();

private:
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	std::vector<Texture> textures;

};

