#include "Application.h"
#include "MeshImporter.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ModuleTexture.h"

MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}

bool MeshImporter::ImportMesh(const char * path)
{

	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{


		ProcessNode(scene->mRootNode, scene);
		//SetInfo(scene->mRootNode);

		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading mesh path: %s", path);
		ret = false;
	}

	return SaveMesh(path);
}

bool MeshImporter::SaveMesh(const char * path)
{
	return false;
}

bool MeshImporter::LoadMesh(const char * path, char*buffer)
{
	char* cursor = buffer;
	// amount of indices / vertices / colors / normals / texture_coords
	uint ranges[2];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);

	uint num_vertices = ranges[0];
	uint num_indices = ranges[1];

	// Load indices
	cursor += bytes;
	bytes = sizeof(Vertex) * num_vertices;
	std::vector<Vertex> vertices;
	vertices.reserve(bytes);

	memcpy(vertices.data(), cursor, bytes);

	cursor += bytes;
	bytes = sizeof(uint) * num_indices;
	std::vector<uint> indices;
	indices.reserve(bytes);

	memcpy(indices.data(), cursor, bytes);
	return false;
}

void MeshImporter::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void MeshImporter::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{

	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	uint ranges[2] = { mesh->mNumVertices,mesh->mNumFaces };

	uint size = sizeof(ranges) + sizeof(uint) * mesh->mNumFaces + sizeof(Vertex) * mesh->mNumVertices;
	char* data = new char[size]; // Allocate
	char* cursor = data;
	uint bytes = sizeof(ranges); // First store ranges

	memcpy(cursor, ranges, bytes);
	cursor += bytes; // Store indices
	bytes = sizeof(Vertex) * mesh->mNumVertices;

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		float3 data;
		//Vertices
		if (mesh->HasPositions())
		{
			data.x = mesh->mVertices[i].x;
			data.y = mesh->mVertices[i].y;
			data.z = mesh->mVertices[i].z;
			vertex.position = data;
		}
		//Normals

		if (mesh->HasNormals())
		{
			data.x = mesh->mNormals[i].x;
			data.y = mesh->mNormals[i].y;
			data.z = mesh->mNormals[i].z;
			vertex.normals = data;
		}
		//Texture coordenate
		float2 tex_color;
		if (mesh->HasTextureCoords(0))
		{
			tex_color.x = mesh->mTextureCoords[0][i].x;
			tex_color.y = mesh->mTextureCoords[0][i].y;
			vertex.tex_coords = tex_color;
		}
		else
			vertex.tex_coords = float2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	memcpy(cursor, vertices.data(), bytes);
	cursor += bytes; // Store indices
	bytes = sizeof(uint) * mesh->mNumFaces;

	//Indices
	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		if (face.mNumIndices != 3) {
			LOG("Number of indices is not 3!");
		}
		else
		{
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);

			}
		}
	}
	memcpy(cursor, indices.data(), bytes);


	//Material
	if (mesh->mMaterialIndex >= 0)
	{
		std::vector<Texture> textures;

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		//Load diffuse data
		std::vector<Texture> diffuse_map = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());
	}

}

std::vector<Texture> MeshImporter::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		//iterate texture_loaded if they have the same push back again the same texture avoid duplicate
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				//skip active this texture was loaded before
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			//new texture
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			texture.rgba_color = { 1.0f,1.0f,1.0f,1.0f };

			textures.push_back(texture);
			textures_loaded.push_back(texture);  // add on textures_loaded now we can check if this texture was loaded before
		}
	}
	return textures;
}

uint MeshImporter::TextureFromFile(const char *path, const std::string &directory)
{

	std::string filename = std::string(path);
	filename = directory + "Textures/" + filename;
	return App->texture->LoadTextureFromFile(filename.c_str());
}
