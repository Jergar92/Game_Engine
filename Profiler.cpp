#include"Profiler.h"


Profiler::Profiler()
{
}

Profiler::~Profiler()
{
	for (int i = 0; i < titles.size(); i++)
	{
		delete titles[i];

	}
	titles.clear();
}

inline bool Profiler::CreateFrame(char * framename)
{
	name = framename;
	return false;
}

bool Profiler::CreateTitle(char * title)
{
	return false;
}

bool Profiler::CreateCategory(const char * title, char * category)
{
	return false;
}

Title::Title()
{
}

Title::~Title()
{
	for (int i = 0; i < categories.size(); i++)
	{
		delete categories[i];
	}
	categories.clear();
}
