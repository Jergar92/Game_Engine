#ifndef __COMPONENT_CHECKBOX__
#define __COMPONENT_CHECKBOX__
#include "Component.h"
#include "ComponentInteractive.h"

class ComponentCanvas;
class ComponentImage;
class ResourceTexture;

class ComponentCheckBox : public ComponentInteractive
{
public:
	ComponentCheckBox(GameObject* my_go);
	~ComponentCheckBox();

	void Update(float dt);

private:
	void Click();
	void InspectorUpdate();
	bool InspectorCheck(ResourceTexture** state);

	bool actived = false;
	
	void Idle();
	void Hover();
	void Down();

	ComponentCanvas* canvas;
	ComponentImage* box;
	ResourceTexture* hover = nullptr;
	ResourceTexture* pressed = nullptr;
	bool active_text = false;
	bool hover_text = false;
	bool pressed_window = false;
	bool activated = false;
};
#endif