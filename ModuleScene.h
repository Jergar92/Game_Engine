#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "Quadtree.h"
class GameObject;
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

	QuadTree<GameObject*> quadtree;
	Plane_p plane;

public:
	GameObject* GetScene() const;
	void LoadTexture(const char* path);
	void SendGameObject(GameObject* go);
	void SaveScene();

private:
	GameObject* scene_go = nullptr;
	GameObject* selected_go = nullptr;



};