#pragma once
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "Mesh.h"
#include <string>
#include <vector>
struct Texture;
class Model
{
public:
	Model(const char* path);
	~Model();
	void Draw();
	void OnGuiDraw();
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

private:
	bool LoadModel(const char* path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void SetInfo(aiNode * node);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	uint TextureFromFile(const char * path, const std::string & directory);


public:
private:
	std::vector<Mesh> meshes;
	std::string name;
	std::string directory;

	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scale;
};

