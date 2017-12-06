#include "ComponentCanvasRenderer.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentImage.h"
#include "UI.h"
ComponentCanvasRenderer::ComponentCanvasRenderer(GameObject * my_go) :Component(my_go)
{
	component_name = "Canvas Renderer";
	type = CANVAS_RENDER;

}

ComponentCanvasRenderer::~ComponentCanvasRenderer()
{
}

void ComponentCanvasRenderer::Update(float dt)
{
	Canvas->AddCanvasRender(this);
}

void ComponentCanvasRenderer::Draw()
{

	

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


}
