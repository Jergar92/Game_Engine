#pragma once
#include "Module.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "MeshImporter.h"
#include "MaterialImporter.h"
#include <vector>

class GameObject;
class ComponentTransform;
class ComponentMesh;
class ComponentMeshRenderer;
struct Texture;
class ModuleImporter:public Module
{
public:
	ModuleImporter();
	~ModuleImporter();
	bool Start();
	void Import(const char* path);
	void Load(const char* path);

	void LoadMesh(const char* path , ComponentMesh* component);
	int LoadTexture(const char* path, ComponentMeshRenderer* component);

	MaterialImporter material;
	MeshImporter mesh;

private:	
	std::string directory;
	std::string dropped_filedir;


};
