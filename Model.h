#pragma once
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include "MathGeoLib-1.5\src\Math\float3.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "glmath.h"
struct Texture;
class Model
{
public:
	Model();
	~Model();
	void Draw();
	void OnGuiDraw();
	void CleanUp();
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vec3 GetCenter();
	void OverlayTexture(const char* path);
	bool LoadModel(const char* path);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	void SetInfo(aiNode * node);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	uint TextureFromFile(const char * path, const std::string & directory);

	void GenerateCubeModel();
public:
	std::vector<Mesh> meshes;
private:
	std::string name;
	std::string directory;
	AABB cube_model;

	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scale;
	uint triangles=0;
};

