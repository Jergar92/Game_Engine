#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleTexture:public Module
{
public:
	ModuleTexture(bool start_enabled = true);
	~ModuleTexture();
	bool Awake(const JSON_Object* data);
	int LoadTextureFromFile(const char* filename);
	void CreateCheckMateTexture();
	bool Start();
	bool CleanUp();
	const GLuint GetCheckID() ;
private:
	GLuint checkID;
};
