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

void ComponentInteractive::OnPlay()
{
	on_execution = true;

}

void ComponentInteractive::OnPause()
{
	on_execution = false;

}

void ComponentInteractive::OnStop()
{
	on_execution = false;
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

void ComponentInteractive::LinkComponent()
{
	if (canvas== nullptr)
	{
		canvas = FindMyCanvas();
		if (canvas != nullptr)
			canvas->interactive_array.push_back((ComponentInteractive*)this);
	}
}

void ComponentInteractive::SetCurrentFocus(bool state)
{
	has_focus = state;
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
