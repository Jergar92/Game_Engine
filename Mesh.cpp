#include "Mesh.h"
#include "Application.h"

#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_HOVER 128

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures) :vertices(vertices), indices(indices), textures(textures), debug_normals_succes(true)
{
	SetupMesh();
}



Mesh::~Mesh()
{
}

void Mesh::SetupMesh()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &vertex_normals_id);
	glGenBuffers(1, &surface_normals_id);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);


	if (indices.size() % 3 != 0)
	{
		LOG("ERROR is Not multiple of 3!");
		debug_normals_succes = false;
	}
	else {
		std::vector<float3> vertex_normals;
		std::vector<float3> surface_normals;
		//vertex normal loop
		for (uint i = 0; i < indices.size(); i ++)
		{
			int indice_number = indices[i];
			vertex_normals.push_back(vertices[indice_number].position);
			vertex_normals.push_back(vertices[indice_number].position+ vertices[indice_number].normals);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_id);
		glBufferData(GL_ARRAY_BUFFER, vertex_normals.size() * sizeof(float3), &vertex_normals[0], GL_STATIC_DRAW);
		//surface normal loop
		for (uint i= 0; i < indices.size(); i += 3)
		{
			vertexA = vertices[indices[i]].position;
			vertexB = vertices[indices[i + 1]].position;
			vertexC = vertices[indices[i + 2]].position;
			float3 edge1 = vertexB - vertexA;
			float3 edge2 = vertexC - vertexA;
			float3 surface_normal = Cross(edge1, edge2);
			surface_normal.Normalize();


			float3 center_point(
				((vertexA.x + vertexB.x + vertexC.x) / 3),
				((vertexA.y + vertexB.y + vertexC.y) / 3),
				((vertexA.z + vertexB.z + vertexC.z) / 3));

			surface_normals.push_back(center_point);
			surface_normals.push_back(center_point + surface_normal);
		}

		glBindBuffer(GL_ARRAY_BUFFER, surface_normals_id);
		glBufferData(GL_ARRAY_BUFFER, surface_normals.size() * sizeof(float3), &surface_normals[0], GL_STATIC_DRAW);
	}
}

void Mesh::Draw()
{


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	
	for (int i = 0; i < textures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		glColor4f(textures[i].rgba_color.x, textures[i].rgba_color.y, textures[i].rgba_color.z, textures[i].rgba_color.w);

	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	
	//Draw normals
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_REPEAT&&debug_normals_succes)
	{
		DrawVertexNormals();
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_REPEAT&&debug_normals_succes)
	{
		DrawTriangleNormals();
	}


	//Reset TextureColor
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);


}

void Mesh::OnGuiDraw()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::Checkbox("Hide Mesh##hide_mesh", &hide_mesh);
		ImGui::Text("Transformation:");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Position x %.2f y %.2f z %.2f", position.x, position.y, position.z);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Rotation x %.2f y %.2f z %.2f", rotation.GetEuler().x, rotation.GetEuler().y, rotation.GetEuler().z);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Scale x %.2f y %.2f z %.2f", scale.x, scale.y, scale.z);
		ImGui::Text("Geometry");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Triangles %i", triangles);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Vertices %i", vertices_count);
		ImGui::Text("Texture");
			for (int i = 0; i < textures.size(); i++)
			{
				ImGui::Image((GLuint*)textures[i].id, ImVec2(TEXTURE_SIZE, TEXTURE_SIZE), ImVec2(0, 1), ImVec2(1,0), *(ImVec4*)&textures[i].rgba_color);
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Image((GLuint*)textures[i].id, ImVec2(TEXTURE_SIZE_HOVER, TEXTURE_SIZE_HOVER), ImVec2(0,1), ImVec2(1,0), *(ImVec4*)&textures[i].rgba_color);
					ImGui::EndTooltip();
				}
				ImGui::PushItemWidth(200);
				ImGui::Text("Image RGBA");
				//ImGui::InputFloat4("##image_rgba", &textures[i].rgba_color[0],2);
				ImGui::ColorEdit4("##image_rgba", &textures[i].rgba_color.x);

				ImGui::PopItemWidth();
			
			}	
		ImGui::TreePop();
	}
}



void Mesh::SetTransformation(aiMatrix4x4 matrix)
{
	matrix.Decompose(scale, rotation, position);
}

void Mesh::SetName(const char * set_name)
{
	name = set_name;

}

void Mesh::SetTriangles(uint set_triangles)
{
	triangles = set_triangles;
}
void Mesh::SetVertices(uint set_vertices)
{
	vertices_count = set_vertices;
}
const uint Mesh::GetTriangles()
{
	return 	triangles;
}
const uint Mesh::GetVertices()
{
	return vertices_count;
}
const char * Mesh::GetName()
{
	return name.c_str();
}

const aiVector3D Mesh::GetPosition()
{
	return position;
}

const aiQuaternion Mesh::GetRotation()
{
	return rotation;
}

const aiVector3D Mesh::GetScale()
{
	return scale;
}

void Mesh::DrawVertexNormals()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_id);
	glVertexPointer(3, GL_FLOAT, sizeof(float3), NULL);
	glDrawArrays(GL_LINES, 0, indices.size() * 2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::DrawTriangleNormals()
{
	glBindBuffer(GL_ARRAY_BUFFER, surface_normals_id);
	glVertexPointer(3, GL_FLOAT, sizeof(float3), NULL);
	glDrawArrays(GL_LINES, 0, indices.size()*2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Mesh::CleanUp()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	if (debug_normals_succes)
	{
		glDeleteBuffers(1, &vertex_normals_id);
		glDeleteBuffers(1, &surface_normals_id);
	}
	RemoveTextures();
	vertices.clear();
	indices.clear();
	textures.clear();
}

void Mesh::RemoveTextures()
{
	for (int i = 0; i < textures.size(); i++)
	{
		glDeleteTextures(1, &textures[i].id);
	}
}

void Mesh::OverlayTexture(uint id)
{
	RemoveTextures();
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i].id = id;
	}
}

bool Mesh::IsHide()
{
	return hide_mesh == true;
}
