#pragma once
#include "Component.h"
#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float4.h"
struct Texture
{
	uint id;
	std::string name;
	std::string type;
	std::string path;
	float4 rgba_color;

};
class ComponentMesh;
class ResourceTexture;
class ComponentMeshRenderer:public Component
{
public:
	ComponentMeshRenderer(GameObject* my_go);
	~ComponentMeshRenderer();
public:
	void Update(float dt);

	void Draw();
	void InspectorUpdate();
	void CleanUp();
	void SetMesh(ComponentMesh* set_mesh);
	void SetTexture(const std::vector<ResourceTexture*>& texture);
	//Save&Load
	bool SaveComponent(JSONConfig& data)const;
	bool LoadComponent(const JSONConfig& data);
private:


private:
	bool show_mesh_renderer_window = false;

	ComponentMesh* mesh = nullptr;
	uint VBO;//Vertex Buffer Object
	uint EBO;//Element Buffer Object
	std::vector<ResourceTexture*> textures;
	//std::vector<ResourceTexture*> textures
};

