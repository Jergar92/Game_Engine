#pragma once
#include <vector>
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
class GameObject;
class MyQuadTree
{
public:
	MyQuadTree(AABB boundaris);
	MyQuadTree();
	~MyQuadTree();
	
	bool CleanUp();
	bool Insert(GameObject* GameObject);
	void Subdivide();
	void SendGameObjectToChilds();

	//std::vector<GameObject> QueryRange(AABB range);

	//Draw Quadtree
	void SetQuadtree(GameObject* scene);
	void DrawQuadtree();
	

public:
	int capacity = 4;
	AABB boundary;
	std::vector<GameObject*> objects;
private:
	MyQuadTree* north_west = nullptr;
	MyQuadTree* north_east = nullptr;
	MyQuadTree* south_west = nullptr;
	MyQuadTree* south_east = nullptr;
};


