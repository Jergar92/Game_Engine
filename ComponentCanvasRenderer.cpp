#include "ComponentCanvasRenderer.h"
#include "ComponentCanvas.h"

#include "ComponentRectTransform.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentImage.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
ComponentCanvasRenderer::ComponentCanvasRenderer(GameObject * my_go) :Component(my_go)
{
	component_name = "Canvas Renderer";
	type = CANVAS_RENDER;
	canvas=FindMyCanvas();

	glGenBuffers(1, &buffer.VBO);
	glGenBuffers(1, &buffer.EBO);

}

ComponentCanvasRenderer::~ComponentCanvasRenderer()
{
}

void ComponentCanvasRenderer::Update(float dt)
{
	canvas->AddCanvasRender(this);
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
		ProcessImage();
		break;
	default:
		break;
	}
}

uint ComponentCanvasRenderer::GetVBO() const
{
	return buffer.VBO;
}

uint ComponentCanvasRenderer::GetEBO() const
{
	return buffer.EBO;
}

uint ComponentCanvasRenderer::GetImageID()const
{
	return (image!=nullptr)?image->GetImageID():-1;
}

void ComponentCanvasRenderer::ProcessImage()
{	
	//UV Setup
	//0,1-------1,1
	//|	1     /	2|
	//|		/	 |
	//|	0 /		3|
	//0,0-------1,0
	buffer.vertices.clear();
	UpdateVertex();

		CanvasVertex ver;
		ver.position = my_go->GetRectTransform()->GetSouthWest();
		ver.tex_coords = image->GetUV0();
		buffer.vertices.push_back(ver);
		ver.position = my_go->GetRectTransform()->GetNorthWest();
		ver.tex_coords = float2(image->GetUV0().x, image->GetUV1().y);
		buffer.vertices.push_back(ver);

		ver.position = my_go->GetRectTransform()->GetNorthEeast();
		ver.tex_coords = image->GetUV1();
		buffer.vertices.push_back(ver);

		ver.position = my_go->GetRectTransform()->GetSouthEast();
		ver.tex_coords = float2(image->GetUV1().x, image->GetUV0().y);
		buffer.vertices.push_back(ver);

		SetUpCanvas();
}

void ComponentCanvasRenderer::SetUpCanvas()
{
	//
	glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);
	glBufferData(GL_ARRAY_BUFFER, buffer.vertices.size() * sizeof(CanvasVertex), &buffer.vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), &buffer.indices[0], GL_STATIC_DRAW);
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ComponentCanvasRenderer::UpdateVertex()
{

}

ComponentCanvas * ComponentCanvasRenderer::FindMyCanvas()
{
	ComponentCanvas * ret = nullptr;
	ret = ((ComponentCanvas*)my_go->FindComponent(ComponentType::CANVAS));
	if (ret == nullptr)
	{
		GameObject* item = nullptr;
		item = my_go->GetPartent();
		while (item != nullptr)
		{
			ret = ((ComponentCanvas*)my_go->FindComponent(ComponentType::CANVAS));
			if (ret != nullptr)
				break;
			item = item->GetPartent();
		}
	}
	return ret;
}
