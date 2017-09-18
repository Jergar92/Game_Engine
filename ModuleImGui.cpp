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



		if (ImGui::Button("Test Window"))
			show_test_window = !show_test_window;
		if (show_test_window)
		{
			ImGui::ShowTestWindow(&show_test_window);
		}
		if (ImGui::Button("show prove window"))
			show_prove_window = !show_prove_window;
		if (show_prove_window)
		{
			    ImGui::Begin("Prove Window", &show_another_window);
				ImGui::InputInt("input number", &i0);
				ImGui::InputInt("input number", &i1);
				i2 = i1 + i0;
				ImGui::InputInt("input number", &i2);
				ImGui::End();
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


