#pragma once
#include <vector>
#include "Globals.h"
struct QuadPoint
{
	float x = 0.0f;
	float y = 0.0f;
	QuadPoint(float x, float y):x(x),y(y)
	{}

};
struct QuadAABB
{
	QuadPoint centre;
	float half_dimension = 0.0f;
	QuadAABB(QuadPoint centre, float half_dimension):centre(centre), half_dimension(half_dimension)
	{}
	bool Contains(const QuadPoint& pos) const 
	{
		bool ret = false;
		//point inside on X
		if (pos.x<centre.x + half_dimension&&pos.x>centre.x - half_dimension)
		{
		//point inside on Y
			if (pos.y<centre.y + half_dimension&&pos.y>centre.y - half_dimension)
			{
				ret = true;
			}
		}
		return ret;
	}
	bool Intersect(const QuadAABB& other_aabb) const
	{
		bool ret = false;
		//right//left
		if (centre.x + half_dimension > other_aabb.centre.x - other_aabb.half_dimension ||
			centre.x - half_dimension < other_aabb.centre.x + other_aabb.half_dimension)
		{
			//bottom//top
			if (centre.y + half_dimension > other_aabb.centre.y - other_aabb.half_dimension ||
				centre.y - half_dimension < other_aabb.centre.y + other_aabb.half_dimension)
			{
				ret = true;
			}
		}
				
				
			return ret;

	}
};

template <class T>
struct Data
{
	QuadPoint pos;
	T data = nullptr;
	Data(QuadPoint pos, T data) :pos(pos), data(data)
	{}
};

template <class T>
class QuadTree
{
public:
	QuadTree<T>(QuadAABB boundaris);
	QuadTree<T>();	

	~QuadTree<T>();

	bool Insert(Data<T> data);
	void Subdivide();
	std::vector<Data<T>> QueryRange(QuadAABB range);
	
private:

public:
	int capacity = 4;
	QuadAABB boundaris;
	std::vector<Data<T>> objects;
private:
	QuadTree<T>* north_west = nullptr;
	QuadTree<T>* north_east = nullptr;
	QuadTree<T>* south_west = nullptr;
	QuadTree<T>* south_east = nullptr;

};

template <class T>
QuadTree<T>::QuadTree()
{
}

template<class T>
QuadTree<T>::QuadTree(QuadAABB boundaris):boundaris(boundaris), north_west(nullptr), north_east(nullptr), south_west(nullptr), south_east(nullptr)
{

}

template <class T>
QuadTree<T>::~QuadTree()
{
}

template<class T>
bool QuadTree<T>::Insert(Data<T> data)
{
	if (boundaris.centre(d.pos)
		return false;
	
		if (objects.size() < capacity)
		{
			objects.push_back(data);
			return true
		}

		if(north_west==nullptr)
		{
			Subdivide();
		}

		if (north_west->Insert(data))
			return true;
		if (north_east->Insert(data))
			return true; 
		if (south_west->Insert(data))
			return true;
		if (south_east->Insert(data))
			return true;
	
	LOG("QUADTREE ERROR")
	return false;
}

template<class T>
void QuadTree<T>::Subdivide()
{
	float quad_size = boundaris.half_dimension*0.5;
	QuadPoint quad_pos = QuadAABB(boundary.centre.x - quad_size, boundary.centre.y - quad_size;
	north_west = new Quadtree(QuadAABB(quad_pos, quad_size));

	float quad_size = boundaris.half_dimension*0.5;
	QuadPoint quad_pos = QuadAABB(boundary.centre.x + quad_size, boundary.centre.y - quad_size;
	north_west = new Quadtree(QuadAABB(quad_pos, quad_size));

	float quad_size = boundaris.half_dimension*0.5;
	QuadPoint quad_pos = QuadAABB(boundary.centre.x - quad_size, boundary.centre.y + quad_size;
	north_west = new Quadtree(QuadAABB(quad_pos, quad_size));

	float quad_size = boundaris.half_dimension*0.5;
	QuadPoint quad_pos = QuadAABB(boundary.centre.x + quad_size, boundary.centre.y + quad_size;
	north_west = new Quadtree(QuadAABB(quad_pos, quad_size));
}

template<class T>
std::vector<Data<T>> QuadTree<T>::QueryRange(QuadAABB range)
{
	std::vector<Data<T>> ret;
	ret.clear();
	if(!boundaris.Intersect(range))
	{
		return ret;
	}
	for (int i = 0; i < objects.size(), i++)
	{
		if (range.Contains(objects[i].pos))
		{
			ret.push_back(objects[i]);
		}
	}
	if (north_west == nullptr)
	{
		return ret;
	}
	std::vector< Data<T> > temp = north_west->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = north_east->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = south_west->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());

	temp = south_east->queryRange(range);
	pInRange.insert(pInRange.end(), temp.begin(), temp.end());
	
	return ret;
}
