#include "Application.h"
#include "MeshImporter.h"
#include "ComponentMesh.h"
#include "ComponentMeshRenderer.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "ModuleFileSystem.h"
#include "ModuleResourceManager.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include <experimental\filesystem>
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "p2Defs.h"
MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}

bool MeshImporter::ImportMesh(const char * path,const char* name)
{

	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		imported_path = path;
		GameObject* main_go = new GameObject();
		aiMatrix4x4 matrix = scene->mRootNode->mTransformation;
		ProcessTransform(matrix, main_go);
		ProcessNode(scene->mRootNode, scene, main_go);
		main_go->SetName(scene->mRootNode->mName.C_Str());
		JSONConfig config;

		config.OpenArray("GameObject");
		main_go->SaveGameObject(config);
		char* buffer = nullptr;
		uint size = config.Serialize(&buffer);
		std::string file_name = App->file_system->SetExtension(name, "json");
		config.Save(file_name.c_str(),App->file_system->GetMeshesFolder());
		config.CleanUp();

		//Save GameObject prefab
		RELEASE(main_go);
		//delete gameobject
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading mesh path: %s", path);
		ret = false;
	}

	return ret;
}


bool MeshImporter::SaveMesh(ResourceMesh * mesh, int vertices_size, int indices_size, const char* path)
{
	bool ret = false;
	//Set custom format
	uint ranges[2] = { vertices_size,indices_size };
	uint size = sizeof(ranges) + sizeof(uint) * indices_size + sizeof(Vertex) * vertices_size;
	char* data = new char[size]; // Allocate
	char* cursor = data;
	uint bytes = sizeof(ranges); // First store ranges
								 //ranges
	memcpy(cursor, ranges, bytes);
	cursor += bytes; // Store indices
	bytes = sizeof(Vertex) * vertices_size;
	//vertices-normals-cords
	memcpy(cursor, mesh->GetVertices().data(), bytes);// Store vertices-normals-tex-cords
	cursor += bytes;
	//indices		
	bytes = sizeof(uint) * indices_size;
	memcpy(cursor, mesh->GetIndices().data(), bytes);// Store indices

	std::string name = std::to_string(mesh->GetUID());
	ret=App->file_system->CreateOwnFile(name.c_str(), data, size, App->file_system->GetMeshesFolder(), "frog");
	std::string origin_file= App->file_system->SetPathFile(mesh_name.c_str(), App->file_system->GetAssetsMeshFolder());
	RELEASE_ARRAY(data);

	return ret;
}
bool MeshImporter::LoadMesh(char * buffer, ComponentMesh * mesh)
{
	char* cursor = buffer;

	// amount of indices / vertices / normals / texture_coords
	uint ranges[2];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);

	uint num_vertices = ranges[0];
	uint num_indices = ranges[1];
	LOG("Save custom format with:\n num_vertices = %i \n num_indices = %i", num_vertices, num_indices);

	// Load indices
	cursor += bytes;
	bytes = sizeof(Vertex) * num_vertices;
	std::vector<Vertex> vertices((Vertex*)cursor, (Vertex*)cursor + num_vertices);

	cursor += bytes;
	if (num_indices != 0)
	{
		bytes = sizeof(uint) * num_indices;
		std::vector<uint> indices((uint*)cursor, (uint*)cursor + num_indices);
	//	mesh->SetData(vertices, indices, num_vertices, num_indices);
		return true;
	}
	//mesh->SetData(vertices, std::vector<uint>(), num_vertices, num_indices);

	/*
	cursor += bytes;
	bytes = sizeof(Texture) * num_indices;
	std::vector<Texture> textures((Texture*)cursor, (Texture*)cursor + num_textures);
	*/

	return true;
}
bool MeshImporter::LoadMesh(ResourceMesh * r_mesh)
{
	char* buffer = nullptr;

	App->file_system->LoadFile(App->file_system->GetMeshesFolder(), r_mesh->GetLibraryFile().c_str(), &buffer);


	char* cursor = buffer;

	// amount of indices / vertices  / normals / texture_coords
	uint ranges[2];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);

	uint num_vertices = ranges[0];
	uint num_indices = ranges[1];
	LOG("Save custom format with:\n num_vertices = %i \n num_indices = %i", num_vertices, num_indices);

	// Load indices
	cursor += bytes;
	bytes = sizeof(Vertex) * num_vertices;
	std::vector<Vertex> vertices((Vertex*)cursor, (Vertex*)cursor + num_vertices);

	cursor += bytes;
	if (num_indices != 0)
	{
		bytes = sizeof(uint) * num_indices;
		std::vector<uint> indices((uint*)cursor, (uint*)cursor + num_indices);
		r_mesh->SetData(vertices, indices, num_vertices, num_indices);
		r_mesh->SetupMesh();

		return true;
	}
	r_mesh->SetData(vertices, std::vector<uint>(), num_vertices, num_indices);
	r_mesh->SetupMesh();
	RELEASE_ARRAY(buffer);

	//RELEASE(buffer);
	return true;
}
void MeshImporter::ProcessNode(aiNode * node, const aiScene * scene, GameObject* parent)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		
		GameObject* child_go = parent->CreateChild();

		aiMatrix4x4 matrix = node->mTransformation;
		ProcessTransform(matrix, child_go);
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mesh_name = node->mName.C_Str();


		child_go->SetName(mesh_name.c_str());
		ProcessMesh(mesh, scene, child_go);
	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, parent);
	}
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


void MeshImporter::ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject* go)
{

	std::vector<Vertex> vertices;
	std::vector<uint> indices;

	bool  indices_error = false;
	for (uint i = 0; i <mesh->mNumVertices; i++)
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
			indices_error = true;
		}
		else
		{
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);

			}
		}
	}
	std::vector<ResourceTexture*> textures;
	//Material
	if (mesh->mMaterialIndex >= 0)
	{

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		//Load diffuse data
		std::vector<ResourceTexture*> diffuse_map = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());
	}


	uint num_vertices = vertices.size();
	uint num_indices = (indices_error)?0:indices.size();


	//Create Mesh & MeshRenderer

	ComponentMesh* component_mesh = (ComponentMesh*)go->CreateComponent(ComponentType::MESH);
	ResourceMesh* r_mesh = nullptr;

	bool same = false;
	for (std::map<aiMesh *, ResourceMesh*> ::const_iterator it = meshes_load.begin(); it != meshes_load.end(); it++)
	{
		if ((*it).first == mesh)
		{
			r_mesh = (*it).second;
			same = true;
		}

	}
	if (!same)
	{
		r_mesh = (ResourceMesh*)App->resource_manager->CreateResource(ResourceType::R_MESH);
		r_mesh->SetData(vertices, indices, num_vertices, num_indices);
		meshes_load[mesh] = r_mesh;

		std::string name = std::to_string(r_mesh->GetUID());
		std::string origin_file = App->file_system->SetPathFile(mesh_name.c_str(), App->file_system->GetAssetsMeshFolder());
		App->file_system->CreateOwnFile(mesh_name.c_str(), ".", 1, App->file_system->GetAssetsMeshFolder(), "fbx");

		r_mesh->SetLibraryFile(name.c_str(), "frog");
		r_mesh->SetOriginalFile(origin_file.c_str());
		r_mesh->SetMetaFile(origin_file.c_str());
		
		JSONConfig config;
		r_mesh->SaveResource(config);
		char* buffer = nullptr;
		uint config_size = config.Serialize(&buffer);
		config.Save(r_mesh->GetMetaJsonFile().c_str());
		config.CleanUp();

	}
	component_mesh->SetResourceMesh(r_mesh);
	ComponentMeshRenderer* component_mesh_renderer = (ComponentMeshRenderer*)go->CreateComponent(ComponentType::MESH_RENDER);
	//ResourceMesh* r_texture= App->resource_manager->SetData(vertices,indices,num_vertices,num_indices);
	//r_texture->SetTexture(textures);
	component_mesh_renderer->SetTexture(textures);
	component_mesh_renderer->SetMesh(component_mesh);
	/*
	Creo el Recurso
	A ese recurso le asocion el origen y el destino, 
	*/

	
	
	/*
	cursor += bytes;
	bytes = sizeof(Texture) * mesh->mMaterialIndex;
	memcpy(cursor, textures.data(), bytes);// Store textures
	*/
	//SaveGameObjectJSON
	//SaveMesh(r_mesh.uid,data,size,app->file_system->getMeshesFolder())
	if (SaveMesh(r_mesh, num_vertices, num_indices, App->file_system->GetMeshesFolder()))
	{
		LOG("Save %s", go->name.c_str());
	}

}

std::vector<ResourceTexture*> MeshImporter::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<ResourceTexture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		//iterate texture_loaded if they have the same push back again the same texture avoid duplicate
		bool same = false;
		ResourceTexture* texture = nullptr;
		for (std::map<const char *, ResourceTexture*> ::const_iterator it = textures_loaded.begin(); it != textures_loaded.end(); it++)
		{
			if ((*it).first == str.C_Str())
			{
				texture = (*it).second;
				same = true;
			}
			
		}
		if (!same)
		{
			uint UID = TextureFromFile(str.C_Str(), this->directory);
			texture = (ResourceTexture*)App->resource_manager->Get(UID);
			texture->path = str.C_Str();
			textures_loaded[texture->path.c_str()] = texture;

		}
		textures.push_back(texture);

	}
	return textures;
}

uint MeshImporter::TextureFromFile(const char *path, const std::string &directory)
{

	std::string filename = std::string(path);
	filename = directory + "Textures/" + filename;
	App->file_system->CloneFile(filename.c_str(),App->file_system->GetAssetsTextFolder());
	std::string complete_path = PATH( App->file_system->GetAssetsTextFolder(), path);
	
	uint UID = App->resource_manager->Find(complete_path.c_str());
	if (UID == 0)
	{
		UID = App->resource_manager->ImportFile(complete_path.c_str());
	}
	return UID;
}
