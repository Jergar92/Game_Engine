#pragma once
#include "Module.h"
#include "GameObject.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

struct Texture;
class ModuleImporter:public Module
{
public:
	ModuleImporter();
	~ModuleImporter();

	bool LoadModel(const char* path);
	std::vector<Texture> textures_loaded;	// stores all the textures loaded, make sure textures aren't loaded more than once.

	void ProcessTransform(aiMatrix4x4 matrix, ComponentTransform* transform, GameObject* go);
	void ProcessNode(aiNode* node, const aiScene* scene, GameObject* parent);
	void ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject* go);
	std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);
	uint TextureFromFile(const char * path, const std::string & directory);
private:	
	std::string directory;


};

