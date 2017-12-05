#pragma once
#include "Globals.h"
#include "Component.h"
#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

struct CanvasVertex
{
	float3 position;
	//float3 normals;
	float2 tex_coords;
};
class ComponentImage;
class Component;
class ComponentCanvasRenderer :public Component
{
public:
	ComponentCanvasRenderer(GameObject* my_go);
	~ComponentCanvasRenderer();

	void Update(float dt);

	void Draw();

	void CleanUp();
	void GetComponent(Component* item);
	void ProcessImage();
	void SetUpCanvas();
	ComponentImage* image;

private:
	std::vector<CanvasVertex> vertices;
	std::vector<uint> indices;
	uint VBO;
	uint EBO;
};

