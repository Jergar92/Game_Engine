#pragma once
#include "UI_Windows.h"
enum SceneState
{
	ON_NONE,
	ON_PLAY,
	ON_PAUSE,
	ON_ONE_FRAME,
	ON_STOP
};
class UI_Play : public UI_Windows
{
public:
	UI_Play(ModuleEditorWindows* my_editor);
	~UI_Play();
	bool Draw();
private:
	float value = 1.0f;

	SceneState state = ON_NONE;
};

