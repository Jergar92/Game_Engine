#include"Profiler.h"


Profiler::Profiler()
{
}

Profiler::~Profiler()
{
	 current_title = nullptr;
	 current_category = nullptr;
	for (int i = 0; i < titles.size(); i++)
	{
		delete titles[i];

	}
	titles.clear();
}

void Profiler::CreateFrame(const char * framename)
{
	if (FrameExist(framename))
	{
		frame_count = frame_time.Read();
		time = frame_time.ReadSec();
		frame_time.Start();
	}
	else
	{
		name = framename;
		frame_time.Start();
	}

}

bool Profiler::CreateTitle(const char * title_name, Title_chain chain )
{
	Title* title = nullptr;
	title = TitleExist(title_name);
	if (title != nullptr)
	{
		current_title->SetValue();
		title->frame_time.Start();
		current_title = title;

	}
	else
	{
		if (current_title != nullptr)
			current_title->SetValue();
		title = new Title(title_name, chain);
		titles.push_back(title);
		title->frame_time.Start();
		current_title = title;


	}
	return false;
}

bool Profiler::CreateCategory(const char * title_name, char * category_name)
{
	Title* title = nullptr;
	title = TitleExist(title_name);
	if (title != nullptr)
	{
		Category* category = nullptr;
		category = title->CategotyExist(category_name);
		if (category != nullptr)
		{

			current_category->GetTime();
			category->frame_time.Start();
			current_category=category;

		}
		else
		{
			if (current_category != nullptr)
				current_category->GetTime();
			category = new Category(category_name);
			title->categories.push_back(category);
			category->frame_time.Start();
			current_category = category;

		}
	
	}
	return false;
}

void Profiler::DrawProfiler()
{
	if (name.empty())
		return;
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	if (!ImGui::Begin("Profiler", &frame, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	if (ImGui::TreeNode(name.c_str()))
	{

		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ms: %i", frame_count);

		for (int i = 0; i < titles.size(); i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, titles[i]->name.c_str()))
			{
				
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ms: %i", titles[i]->frame_count);

				for (int j= 0; j < titles[i]->categories.size(); j++)
				{

					if (ImGui::TreeNode((void*)(intptr_t)j, titles[i]->categories[j]->name.c_str()))
					{
					
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ms: %i", titles[i]->categories[j]->frame_count);
						ImGui::TreePop();
					}	
				}
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}
	ImGui::End();

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

Title::Title(const char * titlename, Title_chain chain):current_chain_state(chain)
{
	name = titlename;
}

Title::~Title()
{
	for (int i = 0; i < categories.size(); i++)
	{
		delete categories[i];
	}
	categories.clear();
}

void Title::SetValue()
{
	switch (current_chain_state)
	{
	case Title_chain::FRONT:
	case Title_chain::MIDDLE:
		SetStack();
	case Title_chain::BACK:
		SetStack();
		frame_count = frame_stack;
		frame_stack = 0;
		break;
	default:
		break;
	}
}

void Title::SetStack()
{
	frame_stack += frame_time.Read();
}

void Title::GetTime()
{
	frame_count = frame_time.Read();

	frame_time.Start();
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
	name = titlename;

}

Category::~Category()
{
}

void Category::GetTime()
{
	frame_count = frame_time.Read();
	frame_time.Start();
}


