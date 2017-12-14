#include "GameObject.h"
#include "ComponentText.h"
#include "ComponentImage.h"
#include "ComponentCanvasRenderer.h"
#include "ComponentCanvas.h"
#include "ComponentRectTransform.h"
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
	if (canvas != nullptr)
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
uint ComponentCanvasRenderer::GetImageID()const
{
	return (image!=nullptr)?image->GetImageID():-1;
}

void ComponentCanvasRenderer::ProcessImage()
{	
	if (image == nullptr)
		return;
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
}

void ComponentCanvasRenderer::ProcessText()
{
	if (text->text_str.empty())
		return;
	const std::string str = text->text_str;
	buffer.vertices.clear();
	buffer.indices.clear();

	uint lastIndex = 0;
	float offsetX = 0, offsetY = 0;
	for (auto c : str)
	{
		GlyphData data = text->getGlyphInfo(c, offsetX, offsetY);
		offsetX = data.offset_x;
		offsetY = data.offset_y;

		CanvasVertex ver0;
		ver0.position=data.positions[0];
		ver0.tex_coords = data.text_cords[0];
		buffer.vertices.push_back(ver0);

		CanvasVertex ver1;
		ver1.position = data.positions[1];
		ver1.tex_coords = data.text_cords[1];
		buffer.vertices.push_back(ver1);

		CanvasVertex ver2;
		ver2.position = data.positions[2];
		ver2.tex_coords = data.text_cords[2];
		buffer.vertices.push_back(ver2);

		CanvasVertex ver3;
		ver3.position = data.positions[3];
		ver3.tex_coords = data.text_cords[3];
		buffer.vertices.push_back(ver3);

		buffer.indices.push_back(lastIndex);
		buffer.indices.push_back(lastIndex + 1);
		buffer.indices.push_back(lastIndex + 2);
		buffer.indices.push_back(lastIndex);
		buffer.indices.push_back(lastIndex + 2);
		buffer.indices.push_back(lastIndex + 3);

		lastIndex += 4;
	}


	glGenBuffers(1, &buffer.VBO);
	glGenBuffers(1, &buffer.EBO);

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
