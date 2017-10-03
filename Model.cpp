#include "Model.h"

Model::Model(const char* path)
{
	LoadModel(path);
}

Model::~Model()
{
}

void Model::Draw()
{
	meshes[0].Draw();
}

bool Model::LoadModel(const char * path)
{
	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array

		ProcessNode(scene->mRootNode, scene);

		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading mesh path: %s", path);
		ret =false;
	}

	return ret;
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{

	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	std::vector<Texture> textures;
	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		float3 data;
		if (mesh->HasPositions())
		{
			data.x = mesh->mVertices[i].x;
			data.y = mesh->mVertices[i].y;
			data.z = mesh->mVertices[i].z;
			vertex.position = data;
		}
		if (mesh->HasNormals())
		{
			data.x = mesh->mNormals[i].x;
			data.y = mesh->mNormals[i].y;
			data.z = mesh->mNormals[i].z;
			vertex.normals = data;
		}
		float2 tex_color;
		if (mesh->HasTextureCoords(0))
		{
			tex_color.x = 0;
			tex_color.y = 0;
			vertex.tex_coords = tex_color;
		}
		vertices.push_back(vertex);
	}
	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	return Mesh(vertices, indices, textures);
}
