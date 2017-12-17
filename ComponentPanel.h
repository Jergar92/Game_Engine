#pragma once
#include "Globals.h"
#include "ComponentInteractive.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

class ResourceTexture;

class ComponentPanel :public ComponentInteractive
{
public:
	ComponentPanel(GameObject* my_go);
	~ComponentPanel();
	void Update(float dt);

	void InspectorUpdate();



	void Idle();
	void Hover();
	void Down();

	bool SaveComponent(JSONConfig & config) const;
	bool LoadComponent(const JSONConfig & config);

	void CleanUp();


private:


	bool show_mesh_renderer_window = false;


};