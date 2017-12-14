#pragma once
#include "Globals.h"
#include "Component.h"
#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

class ComponentText;
class ComponentImage;
class Component;
class ComponentCanvas;

struct CanvasVertex;

struct CanvasBuffer
{
	CanvasBuffer();
	std::vector<CanvasVertex> vertices;
	std::vector<uint> indices;


	uint VBO = 0;
	uint EBO = 0;

};

struct CanvasVertex
{
	float3 position;
	//float3 normals;
	float2 tex_coords;
};
class ComponentCanvasRenderer :public Component
{
public:
	ComponentCanvasRenderer(GameObject* my_go);
	~ComponentCanvasRenderer();

	void Update(float dt);
	void CleanUp();
	void GetComponent(Component* item);
	uint GetImageID()const;
	uint GetVBO()const;
	uint GetEBO()const;
	uint GetIndicesSize() const;
	void ProcessImage();
	void ProcessText();

	void SetUpCanvas();
	void UpdateVertex();

	ComponentCanvas* FindMyCanvas();
	ComponentImage* image = nullptr;
	ComponentText* text=nullptr;

	CanvasBuffer buffer;

private:
	ComponentCanvas* canvas = nullptr;

};

