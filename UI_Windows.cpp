#include "UI_Windows.h"



UI_Windows::UI_Windows()
{
}


UI_Windows::~UI_Windows()
{
}

bool UI_Windows::Draw()
{
	return true;
}

bool UI_Windows::IsActive() const
{
	return active_draw;
}

void UI_Windows::ChangeActive()
{
	active_draw = !active_draw;
}

void UI_Windows::CleanUp()
{
}
