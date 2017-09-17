#include "Globals.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
ModuleImGui::ModuleImGui(Application* app, bool start_enabled):Module(app,start_enabled)
{
	show_test_window = true;
	show_another_window = false;
	clear_color = ImColor(114, 144, 154);
}

ModuleImGui::~ModuleImGui()
{
}

// PreUpdate: clear buffer
update_status ModuleImGui::PreUpdate(float dt)
{
	ImGui_ImplSdlGL2_NewFrame(App->window->window);

	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Test Window")) show_test_window ^= 1;
		if (ImGui::Button("Another Window")) show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleImGui::Update(float dt)
{

	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui::Render();

	return UPDATE_CONTINUE;
}

bool ModuleImGui::CleanUp()
{
	LOG("Cleaning imGui");

	return true;
}
