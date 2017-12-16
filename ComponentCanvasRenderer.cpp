#include "GameObject.h"
#include "ComponentText.h"
#include "ComponentImage.h"
#include "ComponentCanvasRenderer.h"
#include "ComponentCanvas.h"
#include "ComponentRectTransform.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "SDL\include\SDL.h"
#include "SDL_ttf\include\SDL_ttf.h"
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
	if (canvas != nullptr)
		canvas->AddCanvasRender(this);
}




void ComponentCanvasRenderer::CleanUp()
{
	buffer.vertices.clear();
	buffer.indices.clear();
	glDeleteBuffers(1, &buffer.VBO);
	glDeleteBuffers(1, &buffer.EBO);
}

void ComponentCanvasRenderer::GetComponent(Component * item)
{
	switch (item->type)
	{
	case CANVAS_IMAGE:
		image = (ComponentImage*)item;
		ProcessImage();
		break;
	case CANVAS_TEXT:
		text = (ComponentText*)item;
		ProcessText();
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
uint ComponentCanvasRenderer::GetIndicesSize() const
{
	return buffer.indices.size();
}
bool ComponentCanvasRenderer::ProcessComponent()
{
	if (image != nullptr || text != nullptr)
		return (image != nullptr) ? ProcessImage() : ProcessText();
	return false;
}
uint ComponentCanvasRenderer::GetImageID()const
{
	if(image!=nullptr||text!=nullptr)
	return (image!=nullptr)?image->GetImageID():text->id;
}

bool ComponentCanvasRenderer::ProcessImage()
{	
	if (image == nullptr)
		return false;
	//UV Setup
	//0,1-------1,1
	//|	1     /	2|
	//|		/	 |
	//|	0 /		3|
	//0,0-------1,0
	buffer.vertices.clear();
	buffer.indices.clear();

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

		uint lastIndex = 0;

		buffer.indices.push_back(lastIndex);
		buffer.indices.push_back(lastIndex + 1);
		buffer.indices.push_back(lastIndex + 2);
		buffer.indices.push_back(lastIndex + 2);
		buffer.indices.push_back(lastIndex + 3);
		buffer.indices.push_back(lastIndex );
		SetUpCanvas();
		return true;
}

bool ComponentCanvasRenderer::ProcessText()
{
	if (text->text_str.empty())
	{
		return false;
	}
	if (!text->GetUpdateText())
		return true;



	buffer.vertices.clear();
	buffer.indices.clear();

	
	float3 position;
	float2 text_cord;
		CanvasVertex ver0;
		ver0.position=float3(0,0,0);
		ver0.tex_coords = float2(0, 0);
		buffer.vertices.push_back(ver0);

		CanvasVertex ver1;
		ver1.position = float3(0+text->GetRect().width, 0, 0);
		ver1.tex_coords = float2(1, 0);
		buffer.vertices.push_back(ver1);

		CanvasVertex ver2;
		ver2.position = float3(0 + text->GetRect().width, 0 + text->GetRect().height, 0);
		ver2.tex_coords = float2(1, 1);
		buffer.vertices.push_back(ver2);

		CanvasVertex ver3;
		ver3.position = float3(0, 0+ text->GetRect().height, 0);
		ver3.tex_coords = float2(0, 1);
		buffer.vertices.push_back(ver3);
		
		uint lastIndex = 0;
		buffer.indices.push_back(lastIndex);
		buffer.indices.push_back(lastIndex + 1);
		buffer.indices.push_back(lastIndex + 2);
		buffer.indices.push_back(lastIndex + 2);
		buffer.indices.push_back(lastIndex + 3);
		buffer.indices.push_back(lastIndex);





	glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);
	glBufferData(GL_ARRAY_BUFFER, buffer.vertices.size() * sizeof(CanvasVertex), &buffer.vertices[0], GL_STATIC_DRAW);

	if (buffer.indices.size() != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.indices.size()* sizeof(uint), &buffer.indices[0], GL_STATIC_DRAW);
		//set bind buffer glBindBuffer to 0
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	//set bind buffer glBindBuffer to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	text->SetUpdateText(false);
	return true;
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
			ret = ((ComponentCanvas*)item->FindComponent(ComponentType::CANVAS));
			if (ret != nullptr)
				break;
			item = item->GetPartent();
		}
	}
	return ret;
}
