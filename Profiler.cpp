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
	if (FrameExist(framename))
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

void Profiler::DrawProfiler()
{
	if (name.empty())
		return;

	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::SameLine();
		ImGui::Text("Time: %.2f", time);
		for (int i = 0; i < titles.size(); i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, titles[i]->name.c_str()))
			{
				ImGui::SameLine();
				ImGui::Text("Time: %.2f", titles[i]->time);
				for (int j= 0; j < titles[i]->categories.size(); j++)
				{

					if (ImGui::TreeNode((void*)(intptr_t)j, titles[i]->categories[j]->name.c_str()))
					{
						ImGui::Text("Time: %.2f", titles[i]->categories[j]->time);
						ImGui::TreePop();
					}	
				}
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}

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
