#pragma once
#include "Application.h"
#include "ModuleEditorWindows.h"
#include "Globals.h"
#include"p2Defs.h"
enum LoadFile
{
	LOAD_NONE,
	LOAD_MESH,
	LOAD_TEXTURE,
	LOAD_SCENE
};
class GameObject;
class UI_Windows;
class UI_Inspector;
class UI_Hierarchy;
class UI_About;
class UI_Console;
class UI_Folder;
class UI_Play;


class ModuleEditorWindows : public Module
{
public:


	ModuleEditorWindows(bool start_enabled = true);
	~ModuleEditorWindows();

	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);

	update_status GuiUpdate();

	bool CleanUp();

	void SetSceneGameObject(GameObject* set);
	GameObject* GetSelectedGameObject()const;
	void SetSelectedGameObject(GameObject* set);
	void AddLog(const char*fmt, ...);
	void ToLoad(const char* path, LoadFile load);
	void WantToLoad(const char* name, const char*path);
	void WantToSave(const char* name, const char*path);
	std::vector<std::string> ReturnFiles(const char* exclude);
	void WantToUpdate();

	void UpdateFiles();
private:
	void Load();

	bool ShowMenuBar();
	void Configuration();
	void Profiler();
private:
	std::vector<UI_Windows*> ui_windows;
	UI_Inspector* ui_inspector;
	UI_Hierarchy* ui_hierarchy;
	UI_About* ui_about;
	UI_Console* ui_console;
	UI_Folder* ui_folder;
	UI_Play* ui_play;

	bool want_to_save = false;
	std::string path_to_save;
	bool want_to_load = false;
	std::string path_to_load;
	bool want_to_update = false;


	bool wait_load = false;
	LoadFile next_load = LOAD_NONE;

};


