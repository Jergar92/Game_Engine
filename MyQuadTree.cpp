#include "MyQuadTree.h"
#include "Glew\include\GL\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "MathGeoLib-1.5\src\MathGeoLib.h"
#include "GameObject.h"

MyQuadTree::MyQuadTree(AABB boundaris) :boundary(boundaris), north_west(nullptr), north_east(nullptr), south_west(nullptr), south_east(nullptr)
{

}

MyQuadTree::MyQuadTree() : north_west(nullptr), north_east(nullptr), south_west(nullptr), south_east(nullptr)
{

}

MyQuadTree::~MyQuadTree()
{
}


bool MyQuadTree::CleanUp()
{
	bool ret = true;
	
	if (north_west != nullptr)
	{
		north_west->CleanUp();
		RELEASE(north_west);
	}

	if (north_east != nullptr)
	{
		north_east->CleanUp();
		RELEASE(north_east);
	}
	
	if (south_west != nullptr)
	{
		south_west->CleanUp();
		RELEASE(south_west);
	}

	if (south_east != nullptr)
	{
		south_east->CleanUp();
		RELEASE(south_east);
	}

	objects.clear();

	return ret;
}

bool MyQuadTree::RemoveGameObject(const GameObject * remove)
{
	if (north_west != nullptr)
	{

		if (north_west->RemoveGameObject(remove))
		{
			return true;
		}
		else if (north_east->RemoveGameObject(remove))
		{
			return true;
		}
		else if (south_west->RemoveGameObject(remove))
		{
			return true;
		}
		else if (south_east->RemoveGameObject(remove))
		{
			return true;
		}

		for (int i = 0; i < objects.size(); i++)
		{
			GameObject* item = objects[i];

			if (item->GetUID() == remove->GetUID())
			{

				objects.erase(objects.begin() + i);
				return true;
			}
		}

	}
	else
	{
		for (int i = 0; i < objects.size(); i++)
		{
			GameObject* item = objects[i];

			if (item->GetUID() == remove->GetUID())
			{

				objects.erase(objects.begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool MyQuadTree::Insert(GameObject* game_object)
{
	if (!boundary.Contains(game_object->GetBoundingBoxAABB()))
		return false;

	if (north_west != nullptr)
	{

		if (north_west->Insert(game_object))
		{
			return true;
		}
		else if (north_east->Insert(game_object))
		{
			return true;
		}
		else if (south_west->Insert(game_object))
		{
			return true;
		}
		else if (south_east->Insert(game_object))
		{
			return true;
		}
		objects.push_back(game_object);
	}
	else
	{
		objects.push_back(game_object);
		if (objects.size() > capacity)
		{
			Subdivide();
		}
	}
	return true;
}


void MyQuadTree::Subdivide()
{
	float3 quad_size = boundary.HalfSize();

	quad_size.y = boundary.Size().y;

	float3 north_west_quad_pos = float3(boundary.minPoint.x, boundary.minPoint.y, boundary.minPoint.z + quad_size.z);
	north_west = new MyQuadTree(AABB(north_west_quad_pos, north_west_quad_pos + quad_size));

	float3 north_east_quad_pos = float3(boundary.minPoint.x + quad_size.x, boundary.minPoint.y, boundary.minPoint.z + quad_size.z);
	north_east = new MyQuadTree(AABB(north_east_quad_pos, north_east_quad_pos + quad_size));

	float3 south_west_quad_pos = float3(boundary.minPoint.x, boundary.minPoint.y, boundary.minPoint.z);
	south_west = new MyQuadTree(AABB(south_west_quad_pos, south_west_quad_pos + quad_size));

	float3 south_east_quad_pos = float3(boundary.minPoint.x + quad_size.x, boundary.minPoint.y, boundary.minPoint.z);
	south_east = new MyQuadTree(AABB(south_east_quad_pos, south_east_quad_pos + quad_size));

	SendGameObjectToChilds();
}


void MyQuadTree::SendGameObjectToChilds()
{
	std::vector<GameObject*>::iterator it = objects.begin();
	
	while (it != objects.end())
	{
		bool is_erase = false;
		if (north_west->Insert(*it))
		{
			it = objects.erase(it);
			is_erase = true;
		}
		else if (north_east->Insert(*it))
		{
			it = objects.erase(it);
			is_erase = true;
		}
		else if (south_west->Insert(*it))
		{
			it = objects.erase(it);
			is_erase = true;
		}
		else if (south_east->Insert(*it))
		{
			it = objects.erase(it);
			is_erase = true;
		}

		if(is_erase == false)
		it++;
	}
}

void MyQuadTree::CollectCandidates(std::list<GameObject*>& static_list, Frustum camera)
{
	if (camera.ContainsAaBox(boundary))
	{
		for(int i = 0; i < objects.size();i++)
		{
			static_list.push_back(objects[i]);
		}

		if (north_west != nullptr)
		{
			north_west->CollectCandidates(static_list, camera);
			north_east->CollectCandidates(static_list, camera);
			south_west->CollectCandidates(static_list, camera);
			south_east->CollectCandidates(static_list, camera);
		}
	}
}

void MyQuadTree::SetQuadtree(GameObject * scene)
{
	boundary = AABB(float3::zero, 100.0f);
}


void MyQuadTree::DrawQuadtree()
{
	if (north_west == nullptr)
	{
		glBegin(GL_LINES);
		glLineWidth(25.0f);
		glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
		for (uint i = 0; i < 12; i++)
		{
			glVertex3f(boundary.Edge(i).a.x, boundary.Edge(i).a.y, boundary.Edge(i).a.z);
			glVertex3f(boundary.Edge(i).b.x, boundary.Edge(i).b.y, boundary.Edge(i).b.z);
		}
		glEnd();
	}

	
	if (north_west != nullptr)
	{
		north_west->DrawQuadtree();
		north_east->DrawQuadtree();
		south_west->DrawQuadtree();
		south_east->DrawQuadtree();
	}
}


//
//std::vector<GameObject> MyQuadTree::QueryRange(AABB range)
//{
//	std::vector<GameObject> ret;
//	ret.clear();
//	if(!boundaris.Intersect(range))
//	{
//		return ret;
//	}
//	for (int i = 0; i < objects.size(), i++)
//	{
//		if (range.Contains(objects[i].pos))
//		{
//			ret.push_back(objects[i]);
//		}
//	}
//	if (north_west == nullptr)
//	{
//		return ret;
//	}
//	std::vector<GameObject> temp = north_west->queryRange(range);
//	pInRange.insert(pInRange.end(), temp.begin(), temp.end());
//
//	temp = north_east->queryRange(range);
//	pInRange.insert(pInRange.end(), temp.begin(), temp.end());
//
//	temp = south_west->queryRange(range);
//	pInRange.insert(pInRange.end(), temp.begin(), temp.end());
//
//	temp = south_east->queryRange(range);
//	pInRange.insert(pInRange.end(), temp.begin(), temp.end());
//	
//	return ret;
//}
