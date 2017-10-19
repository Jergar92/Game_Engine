#include "MeshImporter.h"



MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}

bool MeshImporter::ImportMesh(const char * path)
{
	return false;
}

void MeshImporter::ProcessTransform(aiMatrix4x4 matrix, ComponentTransform * transform, GameObject * go)
{
}

void MeshImporter::ProcessNode(aiNode * node, const aiScene * scene, GameObject * parent)
{
}

void MeshImporter::ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject * go)
{
}

std::vector<Texture> MeshImporter::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	return std::vector<Texture>();
}

uint MeshImporter::TextureFromFile(const char * path, const std::string & directory)
{
	return uint();
}
