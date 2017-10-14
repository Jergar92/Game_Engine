#include "Model.h"
#include "Application.h"
#include "ModuleTexture.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

Model::Model():triangles(0)
{
}

Model::~Model()
{
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
	if(bounding_box)
	{
		DrawBoundingBox();
	}
	
}

void Model::OnGuiDraw()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::Checkbox("Bounding Box##bounding box", &bounding_box);
		ImGui::Text("Transformation:");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Position x %.2f y %.2f z %.2f", position.x, position.y, position.z);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Rotation x %.2f y %.2f z %.2f", rotation.GetEuler().x, rotation.GetEuler().y, rotation.GetEuler().z);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Scale x %.2f y %.2f z %.2f", scale.x, scale.y, scale.z);
		ImGui::Text("Geometry");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Triangles %i", triangles);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Vertices %i", vertices);

		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i].OnGuiDraw();
		
		}
		ImGui::TreePop();
	}
}

void Model::CleanUp()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].CleanUp();

	}
}

vec3 Model::GetCenter()
{
	GenerateCubeModel();
	float3 center = cube_model.CenterPoint();
	vec3 tmp(center.x, center.y, center.z);
	return tmp;
}

void Model::OverlayTexture(const char * path)
{
	
	uint id=App->texture->LoadTextureFromFile(path);

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].OverlayTexture(id);
	}
}

bool Model::LoadModel(const char * path)
{
	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		
		ProcessNode(scene->mRootNode, scene);
		SetInfo(scene->mRootNode);
		LOG("The model %s with %i triangles was loaded correctly", name.c_str(), triangles);
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
		Mesh newMesh = ProcessMesh(mesh, scene);
		//SetValues
		newMesh.SetTransformation(node->mTransformation);
		newMesh.SetName(node->mName.C_Str());
		newMesh.SetTriangles(mesh->mNumFaces);
		newMesh.SetVertices(mesh->mNumVertices);
		//Push new mesh
		meshes.push_back(newMesh);
	}
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Model::SetInfo(aiNode * node)
{
	
	node->mTransformation.Decompose(position, rotation, scale);
	name = node->mName.C_Str();

	for (int i = 0; i < meshes.size(); i++)
	{
		triangles+=	meshes[i].GetTriangles();
		vertices += meshes[i].GetVertices();
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
			LOG("Number of indices is not 3!")
		}
		else
		{
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);

			}
		}
	}
	//Material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			//Load diffuse data
		std::vector<Texture> diffuse_map = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());

	}

	return Mesh(vertices, indices, textures);
}
std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
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

uint Model::TextureFromFile(const char *path, const std::string &directory)
{

	std::string filename = std::string(path);
	filename = directory +"Textures/"+ filename;
	return App->texture->LoadTextureFromFile(filename.c_str());
}

void Model::DrawBoundingBox()
{
	//--- pos z
	glBegin(GL_LINES);
	glVertex3f(cube_model.maxPoint.x, cube_model.maxPoint.y, cube_model.maxPoint.z);
	glVertex3f(cube_model.maxPoint.x, cube_model.minPoint.y, cube_model.maxPoint.z);

	glVertex3f(cube_model.minPoint.x, cube_model.minPoint.y, cube_model.maxPoint.z);
	glVertex3f(cube_model.minPoint.x, cube_model.maxPoint.y, cube_model.maxPoint.z);
	glEnd();
	//--- pos x
	glBegin(GL_LINES);
	glVertex3f(cube_model.maxPoint.x, cube_model.minPoint.y, cube_model.maxPoint.z);
	glVertex3f(cube_model.maxPoint.x, cube_model.minPoint.y, cube_model.minPoint.z);

	glVertex3f(cube_model.maxPoint.x, cube_model.maxPoint.y, cube_model.minPoint.z);
	glVertex3f(cube_model.maxPoint.x, cube_model.maxPoint.y, cube_model.maxPoint.z);
	glEnd();

	//---- pos y
	glBegin(GL_LINES);
	glVertex3f(cube_model.minPoint.x, cube_model.maxPoint.y, cube_model.maxPoint.z);
	glVertex3f(cube_model.maxPoint.x, cube_model.maxPoint.y, cube_model.maxPoint.z);

	glVertex3f(cube_model.maxPoint.x, cube_model.maxPoint.y, cube_model.minPoint.z);
	glVertex3f(cube_model.minPoint.x, cube_model.maxPoint.y, cube_model.minPoint.z);
	glEnd();

	//--- neg z
	glBegin(GL_LINES);
	glVertex3f(cube_model.minPoint.x, cube_model.minPoint.y, cube_model.minPoint.z);
	glVertex3f(cube_model.minPoint.x, cube_model.maxPoint.y, cube_model.minPoint.z);

	glVertex3f(cube_model.maxPoint.x, cube_model.maxPoint.y, cube_model.minPoint.z);
	glVertex3f(cube_model.maxPoint.x, cube_model.minPoint.y, cube_model.minPoint.z);
	glEnd();

	//--- neg y
	glBegin(GL_LINES);
	glVertex3f(cube_model.minPoint.x, cube_model.minPoint.y, cube_model.minPoint.z);
	glVertex3f(cube_model.maxPoint.x, cube_model.minPoint.y, cube_model.minPoint.z);

	glVertex3f(cube_model.maxPoint.x, cube_model.minPoint.y, cube_model.maxPoint.z);
	glVertex3f(cube_model.minPoint.x, cube_model.minPoint.y, cube_model.maxPoint.z);
	glEnd();

	//--- neg x
	glBegin(GL_LINES);
	glVertex3f(cube_model.minPoint.x, cube_model.minPoint.y, cube_model.minPoint.z);
	glVertex3f(cube_model.minPoint.x, cube_model.minPoint.y, cube_model.maxPoint.z);

	glVertex3f(cube_model.minPoint.x, cube_model.maxPoint.y, cube_model.maxPoint.z);
	glVertex3f(cube_model.minPoint.x, cube_model.maxPoint.y, cube_model.minPoint.z);
	glEnd();
}

void Model::GenerateCubeModel()
{
	cube_model.SetNegativeInfinity();
	for (int i = 0; i < meshes.size(); i++)
	{
		for (int x = 0; x < meshes[i].vertices.size(); x++)
		{
			cube_model.Enclose(meshes[i].vertices[x].position);
		}
	}
}
