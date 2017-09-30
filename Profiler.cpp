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

void Profiler::CreateFrame(char * framename)
{
	if (FrameExist)
	{
		time = frame_time.ReadSec();
		frame_time.Start();
	}
	else
	{
		name = framename;
		frame_time.Start();
	}

}

bool Profiler::CreateTitle(char * title_name)
{
	Title* title = nullptr;
	
	if (title = TitleExist(title_name))
	{
		title->time = title->frame_time.ReadSec();
		title->frame_time.Start();
	}
	else
	{
		title = new Title(title_name);
		titles.push_back(title);
		title->frame_time.Start();

	}
	return false;
}

bool Profiler::CreateCategory(const char * title_name, char * category)
{
	Title* title = nullptr;

	if (title = TitleExist(title_name))
	{
		Category* current_category = nullptr;
		if (current_category = title->CategotyExist(category))
		{
			current_category->time = current_category->frame_time.ReadSec();
			current_category->frame_time.Start();
		}
		else
		{
			current_category = new Category(title_name);
			title->categories.push_back(current_category);
			current_category->frame_time.Start();
		}
	
	}
	return false;
}

bool Profiler::FrameExist(const char * framename)
{
	bool ret = false;
	if (name == framename)
		ret = true;
	return ret;
}

Title* Profiler::TitleExist(const char * titlename)
{
	Title* ret = nullptr;
	for (int i = 0; i < titles.size(); i++)
	{
		if (titles[i]->name == titlename)
			ret = titles[i];
			
	}
	return ret;
}

Title::Title()
{
}

Title::Title(const char * titlename)
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

Category * Title::CategotyExist(const char * titlename)
{
	Category* ret = nullptr;
	for (int i = 0; i < categories.size(); i++)
	{
		if (categories[i]->name == titlename)
			ret = categories[i];

	}
	return ret;
}

Category::Category()
{
}

Category::Category(const char * titlename)
{
}

Category::~Category()
{
}
