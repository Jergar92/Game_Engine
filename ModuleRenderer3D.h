#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "Glew\include\GL\glew.h"
#include "imgui\imgui.h"


#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Awake(const JSONConfig& data);
	update_status PreUpdate(float dt);
	void GuiConfigUpdate();
	update_status GuiUpdate();

	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool SaveConfig(const JSONConfig& data);
	bool LoadConfig(const JSONConfig& data);
	bool CleanUp();
	void OnResize(int width, int height);
private:
	void RenderOptions();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
private:
	int vsync = 0;
	ImVec4 background_color = ImColor(114, 144, 154);


	bool depth_test = true;
	float depth = 1.0f;

	bool cull_face = true;
	int front_face = 1;

	bool lighting = true;
	float light_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	bool color_material = true;
	float color_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float color_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool texture_2d = true;

	bool polygon_smooth = true;

	bool fog = false;
	float fog_density = 0.0f;

	float fog_color[4] = { 0.0f, 0.0f,0.0f, 0.0f };

	bool wireframe = false;

};