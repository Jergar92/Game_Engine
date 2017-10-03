#pragma once
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "Mesh.h"

#include <string>
#include <vector>

class Model
{
public:
	Model(const char* path);
	~Model();
	void Draw();

private:
	bool LoadModel(const char* path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
public:
private:
	std::vector<Mesh> meshes;
	std::string directory;


};

