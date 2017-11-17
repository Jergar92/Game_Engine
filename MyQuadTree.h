#pragma once

#include <vector>
#include <list>
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "MathGeoLib-1.5\src\Math\float2.h"
#include "MathGeoLib-1.5\src\Geometry\Frustum.h"
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
	void CollectCandidates(std::list<GameObject*> &static_list,Frustum Camera);
	//std::vector<GameObject> QueryRange(AABB range);

	//Draw Quadtree
	void SetQuadtree(GameObject* scene);
	void DrawQuadtree();
	

public:
	int capacity = 2;
	AABB boundary;
	std::vector<GameObject*> objects;
private:
	MyQuadTree* north_west = nullptr;
	MyQuadTree* north_east = nullptr;
	MyQuadTree* south_west = nullptr;
	MyQuadTree* south_east = nullptr;
};


