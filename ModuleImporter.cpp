#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleTexture.h"
#include "ModuleScene.h"
#include "ComponentMeshRenderer.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "GameObject.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
ModuleImporter::ModuleImporter()
{
	name = "Importer";
}


ModuleImporter::~ModuleImporter()
{
}

void ModuleImporter::Load(const char * path)
{
	dropped_filedir = path;
	std::size_t found = dropped_filedir.find_last_of('.');
	if (dropped_filedir.substr(found + 1) == "png" || dropped_filedir.substr(found + 1) == "jpg" || dropped_filedir.substr(found + 1) == "dds")
	{
		LoadTexture(dropped_filedir.c_str());

	}
	else
	{
		LoadModel(dropped_filedir.c_str());
	}
}

bool ModuleImporter::LoadModel(const char * path)
{
	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* main_go = new GameObject();

		ComponentTransform* transform = (ComponentTransform*)main_go->CreateComponent(ComponentType::TRANSFORM);
		aiMatrix4x4 matrix = scene->mRootNode->mTransformation;
		ProcessTransform(matrix, transform, main_go);

		ProcessNode(scene->mRootNode, scene, main_go);
		//SetInfo(scene->mRootNode);
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

bool ModuleImporter::LoadTexture(const char * path)
{
	return true;
}

void ModuleImporter::ProcessTransform(aiMatrix4x4 matrix, ComponentTransform* transform, GameObject * go)
{
	aiVector3D scale;
	aiQuaternion rotation;
	aiVector3D position;
	matrix.Decompose(scale, rotation, position);
	//Change transform to mathgeolib
	math::float3 math_scale(scale.x, scale.y, scale.z);
	math::Quat math_rotation(rotation.x, rotation.y, rotation.z, rotation.w);
	math::float3 math_position(position.x, position.y, position.z);
	transform->SetTransform(math_scale, math_rotation, math_position);
	go->AddComponent(transform);
}

void ModuleImporter::ProcessNode(aiNode * node, const aiScene * scene, GameObject* parent)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		GameObject* child_go = new GameObject(parent);
		
		ComponentTransform* transform = (ComponentTransform*)child_go->CreateComponent(ComponentType::TRANSFORM);
		aiMatrix4x4 matrix = node->mTransformation;
		ProcessTransform(matrix, transform, child_go);
		

		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		child_go->SetName(mesh->mName.C_Str());
		ProcessMesh(mesh, scene, child_go);


	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene,parent);
	}
}

void ModuleImporter::ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject* go)
{
	ComponentMesh* component_mesh = (ComponentMesh*)go->CreateComponent(ComponentType::MESH);

	std::vector<Vertex> vertices;
	std::vector<uint> indices;
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

	component_mesh->SetData(vertices, indices);
	go->AddComponent(component_mesh);
	//Material
	if (mesh->mMaterialIndex >= 0)
	{
		ComponentMeshRenderer* component_mesh_renderer = (ComponentMeshRenderer*)go->CreateComponent(ComponentType::MESH_RENDER);
		std::vector<Texture> textures;

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		//Load diffuse data
		std::vector<Texture> diffuse_map = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());

		component_mesh_renderer->SetTexture(textures);
		component_mesh_renderer->SetMesh(component_mesh);
		go->AddComponent(component_mesh_renderer);

	}

}

std::vector<Texture> ModuleImporter::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
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

uint ModuleImporter::TextureFromFile(const char *path, const std::string &directory)
{

	std::string filename = std::string(path);
	filename = directory + "Textures/" + filename;
	return App->texture->LoadTextureFromFile(filename.c_str());
}