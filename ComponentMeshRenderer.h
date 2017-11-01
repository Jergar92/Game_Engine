#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
struct Texture
{
	uint id;
	uint UID;
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
	void InspectorUpdate();
	void SetMesh(ComponentMesh* set_mesh);
	void SetTexture(const std::vector<Texture>& texture);
	//Save&Load
	bool SaveComponent(JSONConfig& data)const;
	bool LoadComponent(const JSONConfig& data);

private:
	ComponentMesh* mesh = nullptr;
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	std::vector<Texture> textures;

};

