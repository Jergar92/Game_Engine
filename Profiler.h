#pragma once
#include "Globals.h"
#include <vector>
#include "Timer.h"
//TODO Add Subcategory

struct Category
{

private:
	Timer frame_time;
	float time = 0.0f;

	std::string name;

};
struct Title
{
	Title();
	~Title();
private:
	Timer frame_time;
	float time = 0.0f;

	std::string name;
	std::vector<Category*> categories;
};

class Profiler
{
public:
	Profiler();
	~Profiler();
	bool CreateFrame(char* framename);
	bool CreateTitle(char* title);
	bool CreateCategory(const char* title,char*category);

private:
	Timer frame_time;
	float time = 0.0f;
	Title* current_title = nullptr;
	Category* current_categoty = nullptr;
	std::string name;
	std::vector<Title*> titles;
	bool categoty_running = false;
	bool frame = false;
};
