#pragma once
#include "Module.h"
#include "Globals.h"
#include "MyQuadTree.h"
#include <list>
class GameObject;
class Plane_p;

class ModuleScene : public Module
{
public:
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status GuiUpdate();

	update_status PreUpdate(float dt);

	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void CleanGO();

	GameObject* GenerateGameObject(GameObject* parent = nullptr);
	GameObject* GetScene() const;
	void EventTry();

	void SendGameObject(GameObject* go);
	void SaveScene(const char* path)const;

	void LoadScene(const char*path);
	void LoadGO(const char*path);

	GameObject* FindGameObjectByID(const std::vector<GameObject*> & go, int UID_to_find)const ;

	//Generate quadtree
	void GenerateQuadTree();
	void GoStaticEnable(bool is_static,GameObject* static_go);
private:

public:

	MyQuadTree* quadtree;
	Plane_p* plane;
	bool enable_draw_quadtree = false;
	std::list<GameObject*> no_static_list;

private:

	GameObject* scene_go = nullptr;

};

