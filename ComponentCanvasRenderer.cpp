#include "ComponentCanvasRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentImage.h"
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
	App->renderer3D->AddCanvasToRender(this);

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
