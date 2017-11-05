#pragma once
#include "Module.h"
#include "Globals.h"
#include "MyQuadTree.h"
class GameObject;
class Plane_p;
class ModuleScene : public Module
{
public:
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status GuiUpdate();

	update_status Update(float dt);
	bool CleanUp();

	void CleanGO();

	GameObject* GenerateGameObject(GameObject* parent = nullptr);

	GameObject* GetScene() const;
	void LoadTexture(const char* path);
	void SendGameObject(GameObject* go);
	void SaveScene(const char* path)const;

	void LoadScene();
	GameObject* FindGameObjectByID(const std::vector<GameObject*> & go, int UID_to_find)const ;
private:

public:

	MyQuadTree<GameObject*> quadtree;
	Plane_p* plane;

private:
	GameObject* scene_go = nullptr;
	GameObject* selected_go = nullptr;



};