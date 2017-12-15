#pragma once
#include "Globals.h"
#include "Resource.h"



typedef struct _TTF_Font TTF_Font;
class ResourceFont:public Resource
{
public:
	ResourceFont(uint UID);
	~ResourceFont();

	void LoadInMemory();
	void Load();
	void UnLoadInMemory();
	void UnLoad();
	TTF_Font* font = NULL;
	int size = 16;
private:

};

