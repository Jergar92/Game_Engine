#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Awake(const JSON_Object * data);
	update_status PreUpdate(float dt);
	void GuiUpdate();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool SaveConfig(const JSON_Object * data);
	bool LoadConfig(const JSON_Object * data);
	bool CleanUp();
	void OnResize(int width, int height);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

private:
	int vsync = 0;
	ImVec4 background_color = ImColor(114, 144, 154);


	bool depth_test = true;
	bool cull_face = true;
	bool lighting = true;
	bool color_material = true;
	bool texture_2d = true;
	bool wireframe = false;

};