#include "ComponentCanvasRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

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
}

void ComponentCanvasRenderer::Draw()
{
}

void ComponentCanvasRenderer::InspectorUpdate()
{
}

void ComponentCanvasRenderer::CleanUp()
{
}
