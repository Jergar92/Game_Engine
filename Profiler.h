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
	void GetTime();
	void StartTime();

	void CategoryDraw(uint label);
	uint GetFrameCount();
	const char* GetName();
	public:

private:
	Timer frame_time;
	uint64_t frame_count = 0;
	std::string name;

};
struct Title
{
public:
	Title();
	Title(const char* titlename);
	Title(const Title&to_copy);
	~Title();
	uint GetFrameCount();
	void TitleDraw(uint label);
	Category* CategotyExist(const char* titlename);
	void SetCategory(Category* set);
	const char* GetName();
private:

public:
private:
	std::string name;
	uint64_t frame_count = 0;
	std::vector<Category*> categories;


};
class Frame
{
public:

	Frame();

	Frame(const char* titlename);
	~Frame();
	void FrameDraw();
	const char* GetName();

private:
	uint GetFrameCount();

public:
	std::vector<Title*> titles;
private:
	std::string name;
	uint64_t frame_count = 0;

};
class Profiler
{
public:
	Profiler();
	~Profiler();
	void CreateFrame(const char* framename);
	void CreateTitles();
	bool CreateTitle(const char* framename,const char* title);
	bool CreateCategory(const char* framename, const char* title,char*category);
	void StopCurrentCategory();
	void DrawProfiler();
	void CopyTitle(const char*from, const char*to);
private:
	bool FrameExist(const char* framename);
	Frame* FindFrame(const char* framename);

	Title* TitleExist(Frame* frame,const char* titlename);

private:

	Title* current_title = nullptr;
	Category* current_category = nullptr;
	std::string name;
	std::vector<Frame*> frames;
	bool categoty_running = false;
	bool frame = true;
};
