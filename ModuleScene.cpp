#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "Primitive.h"


ModuleScene::ModuleScene(bool start_enabled)
{
	name = "Scene";
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	
	
	return ret;
}

update_status ModuleScene::GuiUpdate()
{
	ImGui::Begin("Colision Menu");
	/*
	static int element_1 = 0;
	//------------------Sphere_1------------
	ImGui::PushItemWidth(90);

	ImGui::RadioButton("Sphere", &element_1, 0);
	if (element_1 == 0)
	{
		ImGui::InputFloat("Sphere pos x", &sphere_x, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Sphere pos y", &sphere_y, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Sphere pos z", &sphere_z, 0.1f, 1.0f, 1);
		ImGui::InputFloat("Sphere radius", &sphere_radius, 0.1f, 1.0f, 1);
		if (ImGui::Button("Create##create_sphere"))
		{
			GLAllocateElement(vertex_sphere, sphere_radius);
			CreateSphere(float3(sphere_x, sphere_y, sphere_z), sphere_radius);
			DrawElements();
		}
	}
	ImGui::RadioButton("Cube", &element_1, 1);


	if (element_1 == 1)
	{
		ImGui::InputFloat("Cube pos x", &cube_pos_x, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Cube pos y", &cube_pos_y, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Cube pos z", &cube_pos_z, 0.1f, 1.0f, 1);

		ImGui::InputFloat("Cube size x", &cube_size, 0.1f, 1.0f, 1); ImGui::SameLine();
		if (ImGui::Button("Create##create_cube"))
		{
			GLAllocateElement(vertex_cube, cube_size);
			CreateCube(float3(cube_pos_x, cube_pos_y, cube_pos_z), cube_size);
			DrawElements();
		}
	}
	*/
	ImGui::End();

	return UPDATE_CONTINUE;
}




update_status ModuleScene::Update(float dt)
{
    //Draw modes
	for (int i = 0; i < models.size(); i++)
	{
		models[i]->Draw();
	}	
	plane.Render();

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	return ret;
}
void ModuleScene::LoadModel(const char * path)
{
	models.push_back(new Model(path));
}
