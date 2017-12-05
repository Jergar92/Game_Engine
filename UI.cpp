#include "UI.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


UI::UI()
{
}


UI::~UI()
{
}

void UI::Render()
{
	SetUpCanvas();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

void UI::SetUpCanvas()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UI::AddCanvasRender()
{
}
