#pragma once
#include "Globals.h"
#include <vector>
#include "Timer.h"
#include "imgui\imgui.h"
//TODO Add Subcategory
enum Title_chain
{
	FRONT,
	MIDDLE,
	BACK
};
struct Category
{
	Category();

	Category(const char* titlename);

	~Category();
	void GetTime();
	public:
	Timer frame_time;
	uint64_t frame_count = 0;


	std::string name;

};
struct Title
{
public:
	Title();
	Title(const char* titlename, Title_chain chain_state = MIDDLE);

	~Title();
	void SetValue();
	void SetStack();

	void GetTime();
	Category* CategotyExist(const char* titlename);
public:
	std::string name;
	Timer frame_time;
	uint64_t frame_count = 0;
	uint64_t frame_stack = 0;
	Title_chain current_chain_state = MIDDLE;
	std::vector<Category*> categories;

private:


};

class Profiler
{
public:
	Profiler();
	~Profiler();
	void CreateFrame(const char* framename);
	bool CreateTitle(const char* title, Title_chain chain = MIDDLE);
	bool CreateCategory(const char* title,char*category);
	void DrawProfiler();
private:
	bool FrameExist(const char* framename);
	Title* TitleExist(const char* titlename);

private:
	Timer frame_time;
	uint64_t frame_count = 0;

	float time = 0.0f;
	Title* current_title = nullptr;
	Category* current_category = nullptr;
	std::string name;
	std::vector<Title*> titles;
	bool categoty_running = false;
	bool frame = true;
};
