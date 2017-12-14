#pragma once
#include "Module.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "MeshImporter.h"
#include "MaterialImporter.h"
#include "FontImporter.h"
#include <vector>

class GameObject;
class ComponentTransform;
class ComponentMesh;
class ComponentMeshRenderer;
class ResourceMesh;
class ResourceTexture;

struct Texture;
class ModuleImporter:public Module
{
public:
	ModuleImporter();
	~ModuleImporter();
	bool Start();
	void Import(const char* path);
	bool ImportTexture(const char* path,const char* name);
	bool ImportMesh(const char* path, const char* name);
	bool ImportFont(const char* path, const char* name);

	void LoadMesh(ResourceMesh * mesh);
	int LoadTexture(ResourceTexture* component);

	MaterialImporter material;
	MeshImporter mesh;
	FontImporter font;

private:	
	std::string directory;
	std::string dropped_filedir;


};
