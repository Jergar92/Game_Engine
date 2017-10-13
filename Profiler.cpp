#include"Profiler.h"


Profiler::Profiler()
{
}

Profiler::~Profiler()
{
	 current_title = nullptr;
	 current_category = nullptr;
	 for (int i = 0; i < frames.size(); i++)
	 {
		 delete frames[i];
	 }
	 frames.clear();
}

void Profiler::CreateFrame(const char * framename)
{
	if (!FrameExist(framename))
	{
		Frame* frame = new Frame(framename);
		frames.push_back(frame);
	}

}

void Profiler::CreateTitles()
{
}

bool Profiler::CreateTitle(const char* framename, const char * title_name )
{
	bool ret = true;
	Frame* frame = FindFrame(framename);
	if (frame == nullptr)
	{
		ret = false;
	}
	if (ret == true)
	{
		Title* title = nullptr;

		title = TitleExist(frame, title_name);
		if (title == nullptr)
		{
			title = new Title(title_name);
			frame->titles.push_back(title);
			return ret;
		}
	}
	return ret;
}

bool Profiler::CreateCategory(const char* framename, const char * title_name, char * category_name)
{
	bool ret = true;
	Frame* frame = FindFrame(framename);
	if (frame == nullptr)
	{
		ret = false;
	}
	if (ret == true)
	{
		Title* title = nullptr;
		title = TitleExist(frame, title_name);
		if (title != nullptr)
		{
			Category* category = nullptr;
			category = title->CategotyExist(category_name);
			if (current_category != nullptr)
				current_category->GetTime();
			if (category == nullptr)
			{			
				category = new Category(category_name);
				title->SetCategory(category);
			}
			category->StartTime();
			current_category = category;
		}
	}
	return ret;
}

void Profiler::StopCurrentCategory()
{
	current_category->GetTime();
	current_category = nullptr;
}

void Profiler::DrawProfiler()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	if (!ImGui::Begin("Profiler", &frame, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	for (int i = 0; i < frames.size(); i++)
	{
		Frame* frame_item = frames[i];
		frame_item->FrameDraw();

	}
	ImGui::End();

}

void Profiler::CopyTitle(const char * from, const char * to)
{

	Frame* item_from  = FindFrame(from);
	if (item_from == nullptr)
	{
		LOG("Error can't find the first frame")
			return;
	}
	Frame* item_to = FindFrame(to);
	if (item_to == nullptr)
	{

		LOG("Error can't find the second frame")
			return;
	}
	for (int i = 0; i < item_from->titles.size(); i++)
	{
		Title* to_copy = item_from->titles[i];

		item_to->titles.push_back(new Title(*to_copy));
	}
	
	
}

bool Profiler::FrameExist(const char * framename)
{
	bool ret = false;
	if (name == framename)
		ret = true;
	return ret;
}

Frame * Profiler::FindFrame(const char * framename)
{
	Frame* ret = nullptr;
	for (int i = 0; i < frames.size(); i++)
	{
		Frame* item = frames[i];

		if (strcmp(item->GetName(), framename)==0)
			ret = item;

	}
	return ret;
}

Title* Profiler::TitleExist(Frame* frame,const char * titlename)
{
	Title* ret = nullptr;
	for (int i = 0; i < frame->titles.size(); i++)
	{
		Title* item = frame->titles[i];

		if (strcmp(item->GetName(), titlename) == 0)
			ret = item;
			
	}
	return ret;
}

Title::Title()
{
}

Title::Title(const char * titlename)
{
	name = titlename;
}

Title::Title(const Title &to_copy):name(to_copy.name)
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




void Title::TitleDraw(uint label)
{
	ImGui::Columns(2);
	bool node_open = ImGui::TreeNode((void*)(intptr_t)label, name.c_str());
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ms:  %.2f", GetFrameCount());
	ImGui::Columns(1);

	if (node_open)
	{
		for (int k = 0; k < categories.size(); k++)
		{
			Category* category_item = categories[k];
			category_item->CategoryDraw(k);
		}
		ImGui::TreePop();
	}
}

double Title::GetFrameCount()
{
	frame_count = 0;
	for (int i= 0; i < categories.size(); i++)
	{
		Category* category_item = categories[i];
		frame_count += category_item->GetFrameCount();

	}
	return frame_count;
}

void Title::SetCategory(Category * set)
{
	if (set == nullptr)
	{
		LOG("Category is nullptr");
		return;
	}
	categories.push_back(set);
}



Category * Title::CategotyExist(const char * titlename)
{
	Category* ret = nullptr;
	for (int i = 0; i < categories.size(); i++)
	{
		Category* item = categories[i];
		if (strcmp(item->GetName(), titlename) == 0)
			ret = item;

	}
	return ret;
}

const char * Title::GetName()
{
	return name.c_str();
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

void Category::StartTime()
{
	frame_time.Start();
}

void Category::CategoryDraw(uint label)
{
	ImGui::Columns(2);
	bool node_open = ImGui::TreeNode((void*)(intptr_t)label, name.c_str());
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ms:  %.2f", frame_count);
	if (node_open)
	{
	
		ImGui::TreePop();
	}
	ImGui::Columns(1);
}

double Category::GetFrameCount()
{
	return frame_count;
}

const char * Category::GetName()
{
	return name.c_str();
}

Frame::Frame()
{
}

Frame::Frame(const char * titlename) :name(titlename)
{
}

Frame::~Frame()
{
	for (int i = 0; i < titles.size(); i++)
	{
		delete titles[i];

	}
	titles.clear();
}

void Frame::FrameDraw()
{
	//ImGui::Columns(3, "fsd", false);  // 3-ways, no border
	ImGui::Columns(2);
	bool node_open = ImGui::TreeNode(name.c_str());
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "ms:  %.2f", GetFrameCount());
	ImGui::Columns(1);

	if (node_open)
	{
		for (int j = 0; j < titles.size(); j++)
		{
			Title* title_item = titles[j];
			title_item->TitleDraw(j);	
		}
		ImGui::TreePop();

	}


}

const char * Frame::GetName()
{
	return name.c_str();
}

double Frame::GetFrameCount()
{
	frame_count = 0;
	for (int i = 0; i < titles.size(); i++)
	{
		Title* title_item = titles[i];
		frame_count += title_item->GetFrameCount();

	}
	return frame_count;
}
