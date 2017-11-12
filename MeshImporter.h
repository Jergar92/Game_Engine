#pragma once
#include "Globals.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include <vector>
#include <map>
class GameObject;
class ComponentTransform;
class ComponentMesh;
class ResourceMesh;
class ResourceTexture;

struct Texture;
class MeshImporter
{
public:
	MeshImporter();
	~MeshImporter();

	bool ImportMesh(const char* path, const char* name);
	bool SaveMesh(ResourceMesh * mesh, int vertices_size, int indices_size,const char* path);
	bool LoadMesh(char * buffer, ComponentMesh * mesh);
	bool LoadMesh(ResourceMesh * mesh);

	void ProcessTransform(aiMatrix4x4 matrix,  GameObject * go);
	//std::vector<aiMesh *> mesh_loaded;	// stores all the textures loaded, make sure textures aren't loaded more than once.
	std::map<aiMesh *, ResourceMesh*> meshes_load;
	std::map<const char *, ResourceTexture*> textures_loaded;

	void ProcessNode(aiNode* node, const aiScene* scene, GameObject* parent);
	void ProcessMesh(aiMesh * mesh, const aiScene * scene, GameObject* go);
	std::vector<ResourceTexture*> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);
	uint TextureFromFile(const char * path, const std::string & directory);

private:
	std::string directory;
	std::string imported_path;

	std::string mesh_name;


};

