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

	GameObject* GenerateGameObject(GameObject* parent = nullptr);

	MyQuadTree<GameObject*> quadtree;
	Plane_p* plane;

public:
	GameObject* GetScene() const;
	void LoadTexture(const char* path);
	void SendGameObject(GameObject* go);
	void SaveScene();

	void LoadScene();

private:
	GameObject* scene_go = nullptr;
	GameObject* selected_go = nullptr;



};