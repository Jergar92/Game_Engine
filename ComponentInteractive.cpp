#include "ComponentInteractive.h"
#include "GameObject.h"
#include "ComponentCanvas.h"


ComponentInteractive::ComponentInteractive(GameObject* my_go):Component(my_go)
{
	transform = (ComponentRectTransform*)my_go->FindComponent(RECT_TRANSFORM);
}


ComponentInteractive::~ComponentInteractive()
{
}

void ComponentInteractive::OnIdle()
{
	states = IDLE;
	Idle();
}

void ComponentInteractive::OnHover()
{
	states = HOVER;
	Hover();
}

void ComponentInteractive::OnClick()
{
	states = DOWN;
	Down();
}

void ComponentInteractive::OnDown()
{
	states = DOWN;
	Down();
}

ComponentCanvas * ComponentInteractive::FindMyCanvas()
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