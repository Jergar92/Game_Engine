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
	void InspectorCheck(ResourceTexture** state);

	bool actived = false;

	ComponentCanvas* canvas;
	ComponentImage* check;
	ResourceTexture* empty = nullptr;
	ResourceTexture* checked = nullptr;

	uint id_active;
	uint id_unactive;
};
#endif