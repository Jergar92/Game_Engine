#include "ComponentCanvasRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentImage.h"
#include "ResourceTexture.h"
ComponentCanvasRenderer::ComponentCanvasRenderer(GameObject * my_go) :Component(my_go)
{
	component_name = "Canvas Renderer";
	type = CANVAS_RENDER;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

ComponentCanvasRenderer::~ComponentCanvasRenderer()
{
}

void ComponentCanvasRenderer::Update(float dt)
{
	App->renderer3D->AddCanvasToRender(this);

}

void ComponentCanvasRenderer::Draw()
{

	SetUpCanvas();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (image->GetImage() != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, image->GetImage()->GetID());
		glColor4f(image->GetImage()->GetRGBA().x, image->GetImage()->GetRGBA().y, image->GetImage()->GetRGBA().z, image->GetImage()->GetRGBA().w);
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, sizeof(CanvasVertex), NULL);
	//glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glTexCoordPointer(2, GL_FLOAT, sizeof(CanvasVertex), (void*)offsetof(CanvasVertex, tex_coords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	vertices.clear();
	indices.clear();

}


void ComponentCanvasRenderer::CleanUp()
{
}

void ComponentCanvasRenderer::GetComponent(Component * item)
{
	switch (item->type)
	{
	case CANVAS_IMAGE:
		image = (ComponentImage*)item;
	default:
		break;
	}
}

void ComponentCanvasRenderer::ProcessImage()
{
	std::vector<CanvasVertex> vertices;

	
}

void ComponentCanvasRenderer::SetUpCanvas()
{

	
	CanvasVertex ver1;
	ver1.position = float3(image->GetImageRect().vertices[0], image->GetImageRect().vertices[1], 0);
	ver1.tex_coords = float2(0.0f, 0.0f);
	vertices.push_back(ver1);
	
	CanvasVertex ver2;
	ver2.position = float3(image->GetImageRect().vertices[3], image->GetImageRect().vertices[4], 0);
	ver2.tex_coords = float2(0.0f, 1.0f);
	vertices.push_back(ver2);

	CanvasVertex ver3;
	ver3.position = float3(image->GetImageRect().vertices[6], image->GetImageRect().vertices[7], 0);
	ver3.tex_coords = float2(1.0f, 1.0f);
	vertices.push_back(ver3);

	CanvasVertex ver4;
	ver4.position = float3(image->GetImageRect().vertices[9], image->GetImageRect().vertices[10], 0);
	ver4.tex_coords = float2(1.0f, 0.0f);

	vertices.push_back(ver4);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CanvasVertex), &vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
