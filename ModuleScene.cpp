#include "Application.h"
#include "Globals.h"
#include"ModuleScene.h"
#include "Primitive.h"


ModuleScene::ModuleScene(bool start_enabled)
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//TODO 2
	float cube[] =
	{
		0.0f, 0.0f, 5.0f,
			5.0f, 0.0f, 5.0f,
			5.0f, 5.0f, 5.0f,

			0.0f, 0.0f, 5.0f,
			5.0f, 5.0f, 5.0f,
			0.0f, 5.0f, 5.0f,

			5.0f, 0.0f, 5.0f,
			5.0f, 0.0f, 0.0f,
			5.0f, 5.0f, 5.0f,

			5.0f, 0.0f, 0.0f,
			5.0f, 5.0f, 0.0f,
			5.0f, 5.0f, 5.0f,


			5.0f, 0.0f, 0.0f,
			0.0f, 5.0f, 0.0f,
			5.0f, 5.0f, 0.0f,

			0.0f, 0.0f, 0.0f,
			0.0f, 5.0f, 0.0f,
			5.0f, 0.0f, 0.0f,


			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 5.0f,
			0.0f, 5.0f, 0.0f,

			0.0f, 0.0f, 5.0f,
			0.0f, 5.0f, 5.0f,
			0.0f, 5.0f, 0.0f,


			5.0f, 5.0f, 5.0f,
			5.0f, 5.0f, 0.0f,
			0.0f, 5.0f, 0.0f,

			5.0f, 5.0f, 5.0f,
			0.0f, 5.0f, 0.0f,
			0.0f, 5.0f, 5.0f,


			5.0f, 0.0f, 5.0f,
			0.0f, 0.0f, 5.0f,
			0.0f, 0.0f, 0.0f,

			5.0f, 0.0f, 5.0f,
			0.0f, 0.0f, 0.0f,
			5.0f, 0.0f, 0.0f
	};

	//load buffer
	glGenBuffers(1, (GLuint*)&buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, cube, GL_STATIC_DRAW);

	return ret;
}




update_status ModuleScene::Update(float dt)
{

	/*
	//TODO
	glBegin(GL_TRIANGLES);
	
	//front
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 5.0f, 5.0f);

	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 5.0f, 5.0f);
	glVertex3f(0.0f, 5.0f, 5.0f);

	//Right
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 5.0f);

	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 5.0f);

	//Back
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);

	//left
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(0.0f, 5.0f, 5.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);

	//Up
	glVertex3f(5.0f, 5.0f, 5.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);

	glVertex3f(5.0f, 5.0f, 5.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 5.0f);

	//bottom
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);




	glEnd();
	*/
	//TODO 2 with vertex arrays
	//draw
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,buffer_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);


	ImGui::Begin("Colision Menu");

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
			Sphere_p* item = new Sphere_p(sphere_radius);
			item->SetPos(sphere_x, sphere_y, sphere_z);
			elements.push_back(item);
		}
	}
	ImGui::RadioButton("Cube", &element_1, 1);
	
	if (element_1 == 1)
	{
		ImGui::InputFloat("Cube pos x", &cube_pos_x, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Cube pos y", &cube_pos_y, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Cube pos z", &cube_pos_z, 0.1f, 1.0f, 1);

		ImGui::InputFloat("Cube size x", &cube_size_x, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Cube size y", &cube_size_y, 0.1f, 1.0f, 1); ImGui::SameLine();
		ImGui::InputFloat("Cube size z", &cube_size_z, 0.1f, 1.0f, 1);
		if (ImGui::Button("Create##create_cube"))
		{
			Cube_p* item = new Cube_p(cube_size_x, cube_size_y, cube_size_z);
			item->SetPos(cube_pos_x, cube_pos_y, cube_pos_z);
			elements.push_back(item);
		}
	}

	ImGui::End();

	plane.Render();
	std::list<Primitive*>::iterator item = elements.begin();
	while (item != elements.end())
	{
		item._Ptr->_Myval->Render();
		item++;
	}
	/*cube.Render();*/
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;

	return ret;
}
