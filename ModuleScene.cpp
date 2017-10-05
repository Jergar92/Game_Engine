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
	
	//index
	/*
	GLfloat cube2[] =
	{
		8.0, -1.0, 7.0,
		10.0,-1.0, 7.0,
		10.0, 1.0, 7.0,
		8.0,  1.0, 7.0,
		// back
		8.0, -1.0, 5.0,
		10.0,-1.0, 5.0,
		10.0, 1.0, 5.0,
		8.0,  1.0, 5.0,
	};
	array_index_size = sizeof(cube2);

	glGenBuffers(1, &array_index_id);
	glBindBuffer(GL_ARRAY_BUFFER, array_index_id);
	glBufferData(GL_ARRAY_BUFFER, array_index_size, cube2, GL_STATIC_DRAW);
	

	GLushort cube_id[] =
	{
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	buffer_element_size = sizeof(cube_id);
	glGenBuffers(1, &buffer_element_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_element_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_element_size, cube_id, GL_STATIC_DRAW);

	*/
	
	GLubyte checkImage[64][64][4];
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	
	return ret;
}

update_status ModuleScene::GuiUpdate()
{
	/*
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

	ImGui::End();
	*/
	return UPDATE_CONTINUE;
}
void ModuleScene::cubeDirectMode()
{

	//TODO

	glBindTexture(GL_TEXTURE_2D, App->texture->GetCheckID());
	glBegin(GL_TRIANGLES);
	//front
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, 5.0f);
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(5.0f, 0.0f, 5.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(5.0f, 5.0f, 5.0f);

	glTexCoord2d(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, 5.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(5.0f, 5.0f, 5.0f);
	glTexCoord2d(1.0f,	0.0f);	glVertex3f(0.0f, 5.0f, 5.0f);

	//Right
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(5.0f, 0.0f, 5.0f);
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(5.0f, 5.0f, 5.0f);

	glTexCoord2d(0.0f, 1.0f);	glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(5.0f, 5.0f, 5.0f);

	//Back
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(5.0f, 5.0f, 0.0f);

	glTexCoord2d(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(5.0f, 0.0f, 0.0f);

	//left
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f, 5.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(0.0f, 5.0f, 0.0f);

	glTexCoord2d(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f, 5.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(0.0f, 5.0f, 5.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(0.0f, 5.0f, 0.0f);

	//Up
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(5.0f, 5.0f, 5.0f);
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(0.0f, 5.0f, 0.0f);

	glTexCoord2d(0.0f, 1.0f);	glVertex3f(5.0f, 5.0f, 5.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(0.0f, 5.0f, 5.0f);

	//bottom
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(5.0f, 0.0f, 5.0f);
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f, 5.0f);
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2d(1.0f, 1.0f);	glVertex3f(5.0f, 0.0f, 5.0f);
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(5.0f, 0.0f, 0.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

}
void ModuleScene::CubeIndexMode()
{/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);


	glBindBuffer(GL_ARRAY_BUFFER, array_index_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_element_id);
	glDrawElements(GL_TRIANGLES, sizeof(GLushort) * 72 / 3, GL_UNSIGNED_SHORT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
}


update_status ModuleScene::Update(float dt)
{
    //Draw modes
	for (int i = 0; i < models.size(); i++)
	{
		models[i]->Draw();
	}	
	cubeDirectMode();
	CubeIndexMode();
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
