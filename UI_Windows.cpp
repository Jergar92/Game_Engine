#include "UI_Windows.h"
#include "ModuleEditorWindows.h"


UI_Windows::UI_Windows(ModuleEditorWindows* my_editor):my_editor(my_editor)
{
}


UI_Windows::~UI_Windows()
{
	my_editor = nullptr;
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
