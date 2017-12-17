#ifndef __COMPONENT_BUTTON__
#define __COMPONENT_BUTTON__
#include "ComponentInteractive.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include <map>
class ComponentImage;
class ResourceTexture;

struct State {
	
	float2 uv0;
	float2 uv1;
};

class ComponentButton : public ComponentInteractive
{

public:

	ComponentButton(GameObject* my_go);
	~ComponentButton();

	void Update(float dt);
	void CleanUp();

	bool SaveComponent(JSONConfig & config) const;

	bool LoadComponent(const JSONConfig & config);

	void InspectorUpdate();
	void ShowInfo(ResourceTexture* texture);
	void ButtonFunctionality();
	void StartFunciton(int event_num);
	void Idle();
	void Hover();
	void Down();

private:

	ComponentImage* texture = nullptr;
	ResourceTexture* over_texture = nullptr; 
	ResourceTexture* click_texture = nullptr;
	int function_selection = 0;
	bool InspectorCheck(ResourceTexture** text);
	bool over_window = false;
	bool pressed_window = false;
	bool click_window = false;
	std::map<int,const char*> functions;
};


/*
idle	(0,220),(890,0)
over (895 220) (1786,0)
click (1793,220), (2684,0)
*/
#endif // __COMPONENT_BUTTON__

