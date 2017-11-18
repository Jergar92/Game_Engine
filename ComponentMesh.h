#pragma once
#include "Component.h"

#include "Globals.h"
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"

struct Vertex;
class ResourceMesh;
class ComponentMesh :public Component
{
public:
	ComponentMesh(GameObject* my_go);
	~ComponentMesh();
	void Update(float dt);
	void InspectorUpdate();
	void CleanUp();

	void DrawMesh(bool show);
	
	//Getters
	const std::vector<Vertex>& GetVertices()const;
	const std::vector<uint>& GetIndices()const;
	uint GetVertexBuffer()const;
	uint GetElementBuffer()const;
	uint GetVertexNormalID()const;
	uint GetSurfaceNormalID()const;
	const ResourceMesh* GetResourceMesh()const;
	bool HaveResourceMesh()const;
	bool GetDrawMesh()const;
	bool GetDebugNormal()const;


	//Setters
	void SetResourceMesh(ResourceMesh* mesh);

	//Save&Load
	bool SaveComponent(JSONConfig& data)const;
	bool LoadComponent(const JSONConfig& data);

private:
	
	std::string name;
	bool draw_mesh = true;
	bool debug_normals_succes = false;
	bool show_mesh_window = false;

	AABB bounding_box;
	
	ResourceMesh* r_mesh=nullptr;
};

