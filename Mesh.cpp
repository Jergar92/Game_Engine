#include "Mesh.h"
#include "Application.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures) :vertices(vertices), indices(indices), textures(textures)
{
	SetupMesh();
}



Mesh::~Mesh()
{
}

void Mesh::SetupMesh()
{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);

//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

	std::vector<float3> item_vector;

	for (int i = 0; i < vertices.size(); i++)
	{
		item_vector.push_back(vertices[i].position);
	}
	glGenBuffers(1, &Vector_id);
	glBindBuffer(GL_ARRAY_BUFFER, Vector_id);
	glBufferData(GL_ARRAY_BUFFER, item_vector.size() * sizeof(float3), &item_vector[0], GL_STATIC_DRAW);


	std::vector<float3> item_normals;

	for (int i = 0; i < vertices.size(); i++)
	{
		item_normals.push_back(vertices[i].normals);
	}


	glGenBuffers(1, &Normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, Normal_id);
	glBufferData(GL_ARRAY_BUFFER, item_normals.size() * sizeof(float3), &item_normals[0], GL_STATIC_DRAW);

	std::vector<float2> item_cords;

	for (int i = 0; i < vertices.size(); i++)
	{
		item_cords.push_back(vertices[i].tex_coords);
	}


	glGenBuffers(1, &Cord_id);
	glBindBuffer(GL_ARRAY_BUFFER, Cord_id);
	glBufferData(GL_ARRAY_BUFFER, item_cords.size() * sizeof(float2), &item_cords[0], GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

	//don't work need shaders
	//Position data
	//glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	//Normal data
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	//Texture_cordenates data
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, tex_coords));

//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
}

void Mesh::Draw()
{


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);

	for (int i = 0; i < textures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i].id);

	}
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, Cord_id);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);




	glBindBuffer(GL_ARRAY_BUFFER, Vector_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D,0);

	
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_VERTEX_ARRAY);





}
