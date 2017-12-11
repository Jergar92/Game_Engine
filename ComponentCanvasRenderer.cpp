#include "ComponentCanvasRenderer.h"
#include "ComponentCanvas.h"

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
	default:
		break;
	}
}

void ComponentCanvasRenderer::ProcessImage()
{

	
}

void ComponentCanvasRenderer::SetUpCanvas()
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
