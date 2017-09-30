#pragma once
#include "Globals.h"
#include <vector>
#include "Timer.h"
#include "imgui\imgui.h"
//TODO Add Subcategory

struct Category
{
	Category();

	Category(const char* titlename);

	~Category();
	public:
	Timer frame_time;
	float time = 0.0f;

	std::string name;

};
struct Title
{
public:
	Title();
	Title(const char* titlename);

	~Title();
	Category* CategotyExist(const char* titlename);
public:
	std::string name;
	Timer frame_time;
	float time = 0.0f;
	std::vector<Category*> categories;

private:


};

class Profiler
{
public:
	Profiler();
	~Profiler();
	void CreateFrame(const char* framename);
	bool CreateTitle(const char* title);
	bool CreateCategory(const char* title,char*category);
	void DrawProfiler();
private:
	bool FrameExist(const char* framename);
	Title* TitleExist(const char* titlename);

private:
	Timer frame_time;
	float time = 0.0f;
	Title* current_title = nullptr;
	Category* current_categoty = nullptr;
	std::string name;
	std::vector<Title*> titles;
	bool categoty_running = false;
	bool frame = true;
};
