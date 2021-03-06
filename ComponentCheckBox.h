#ifndef __COMPONENT_CHECKBOX__
#define __COMPONENT_CHECKBOX__
#include "Component.h"
#include "ComponentInteractive.h"
#include <map>

class ComponentCanvas;
class ComponentImage;
class ResourceTexture;

class ComponentCheckBox : public ComponentInteractive
{
public:
	ComponentCheckBox(GameObject* my_go);
	~ComponentCheckBox();
	void OnPlay();

	void Update(float dt);

private:
	void Click();
	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);
	void CleanUp();
	void InspectorUpdate();
	void StartFunciton(int event_num);
	bool InspectorCheck(ResourceTexture** state);

	bool actived = false;
	
	void Idle();
	void Hover();
	void Down();
	int function_selection = 0;
	std::map<int, const char*> functions;

	ComponentImage* box;
	ResourceTexture* hover = nullptr;
	ResourceTexture* pressed = nullptr;
	bool active_text = false;
	bool hover_text = false;
	bool pressed_window = false;
	bool activated = false;
};
#endif