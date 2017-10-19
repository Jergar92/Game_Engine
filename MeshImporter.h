#pragma once
#include "Globals.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include <vector>

class GameObject;
class ComponentTransform;
struct Texture;
class MeshImporter
{
public:
	MeshImporter();
	~MeshImporter();

	bool ImportMesh(const char* path);
	bool SaveMesh(const char* name);
	bool LoadMesh(const char* path, char*buffer);

	void ProcessTransform(aiMatrix4x4 matrix,  GameObject * go);

	std::vector<Texture> textures_loaded;	// stores all the textures loaded, make sure textures aren't loaded more than once.
	void ProcessNode(aiNode* node, const aiScene* scene, GameObject* parent);
	void ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject* go);
	std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);
	uint TextureFromFile(const char * path, const std::string & directory);

private:
	std::string directory;



};

