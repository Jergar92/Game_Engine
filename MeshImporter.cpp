#include "Application.h"
#include "MeshImporter.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "ModuleFileSystem.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "p2Defs.h"
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
		GameObject* main_go = App->scene->GenerateGameObject();
		aiMatrix4x4 matrix = scene->mRootNode->mTransformation;
		ProcessTransform(matrix, main_go);
		ProcessNode(scene->mRootNode, scene, main_go);
		main_go->SetName(scene->mRootNode->mName.C_Str());
		App->scene->SendGameObject(main_go);
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading mesh path: %s", path);
		ret = false;
	}

	return ret;
}


bool MeshImporter::SaveMesh(const char * name, char * buffer, int buffer_size,const char * path)
{
	return App->file_system->CreateOwnFile(name, buffer, buffer_size, path,"frog");;
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
	std::vector<Vertex> vertices((Vertex*)cursor, (Vertex*)cursor + num_vertices);

	cursor += bytes;
	if (num_indices != 0)
	{
		bytes = sizeof(uint) * num_indices;
		std::vector<uint> indices((uint*)cursor, (uint*)cursor + num_indices);
	}
	/*
	cursor += bytes;
	bytes = sizeof(Texture) * num_indices;
	std::vector<Texture> textures((Texture*)cursor, (Texture*)cursor + num_textures);
	*/
	return false;
}

void MeshImporter::ProcessTransform(aiMatrix4x4 matrix, GameObject * go)
{
	aiVector3D scale;
	aiQuaternion rotation;
	aiVector3D position;
	matrix.Decompose(scale, rotation, position);
	//Change transform to mathgeolib
	math::float3 math_scale(scale.x, scale.y, scale.z);
	math::Quat math_rotation(rotation.x, rotation.y, rotation.z, rotation.w);
	math::float3 math_position(position.x, position.y, position.z);
	go->SetTransform(math_scale, math_rotation, math_position);
}
void MeshImporter::ProcessNode(aiNode * node, const aiScene * scene, GameObject* parent)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		GameObject* child_go = new GameObject(parent);
		aiMatrix4x4 matrix = node->mTransformation;
		ProcessTransform(matrix, child_go);
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		child_go->SetName(node->mName.C_Str());
		ProcessMesh(mesh, scene, child_go);
	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene,parent);
	}
}

void MeshImporter::ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject* go)
{

	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	uint num_vertices = mesh->mNumVertices;
	uint num_indices = mesh->mNumFaces;
	bool  indices_error = false;
	for (uint i = 0; i <num_vertices; i++)
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
			LOG("x%.2f,y%.2f,z%.2f", vertex.position.x, vertex.position.y, vertex.position.z);
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


	//Indices
	for (uint i = 0; i < num_indices; i++)
	{
		aiFace face = mesh->mFaces[i];
		if (face.mNumIndices != 3) {
			LOG("Number of indices is not 3!");
			num_indices=0;
		}
		else
		{
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);

			}
		}
	}
	std::vector<Texture> textures;
	//Material
	if (mesh->mMaterialIndex >= 0)
	{

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		//Load diffuse data
		std::vector<Texture> diffuse_map = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());
	}

	//Create Mesh & MeshRenderer
	ComponentMesh* component_mesh = (ComponentMesh*)go->CreateComponent(ComponentType::MESH);
	component_mesh->SetData(vertices, indices, num_vertices, num_indices);
	go->AddComponent(component_mesh);
	ComponentMeshRenderer* component_mesh_renderer = (ComponentMeshRenderer*)go->CreateComponent(ComponentType::MESH_RENDER);
	component_mesh_renderer->SetTexture(textures);
	component_mesh_renderer->SetMesh(component_mesh);
	go->AddComponent(component_mesh_renderer);

	
	//Set custom format

	uint ranges[2] = { num_vertices,num_indices };
	uint size = sizeof(ranges) + sizeof(uint) * mesh->mNumFaces + sizeof(Vertex) * mesh->mNumVertices;
	char* data = new char[size]; // Allocate
	char* cursor = data;
	uint bytes = sizeof(ranges); // First store ranges
	//ranges
	memcpy(cursor, ranges, bytes);
	cursor += bytes; // Store indices
	bytes = sizeof(Vertex) *num_vertices;
	//vertices-normals-cords
	memcpy(cursor, vertices.data(), bytes);// Store vertices-normals-tex-cords
	cursor += bytes; 
	//indices		
	bytes = sizeof(uint) * num_indices;
	memcpy(cursor, indices.data(), bytes);// Store indices
	
	/*
	cursor += bytes;
	bytes = sizeof(Texture) * mesh->mMaterialIndex;
	memcpy(cursor, textures.data(), bytes);// Store textures
	*/
	if (SaveMesh(go->name.c_str(), data, size, App->file_system->GetMeshesFolder()))
	{
		LOG("Save %s", go->name.c_str());
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
	return App->importer->material.ImportTexture(filename.c_str());
}
