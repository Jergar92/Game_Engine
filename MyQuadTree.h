#pragma once
#include <vector>
#include "Globals.h"
#include "MathGeoLib-1.5\src\Geometry\AABB.h"
#include "MathGeoLib-1.5\src\Math\float2.h"

template <class T>
struct Data
{
	float2 pos;
	T data = nullptr;
	Data(float2 pos, T data) :pos(pos), data(data)
	{}
};

template <class T>
class MyQuadTree
{
public:
	MyQuadTree<T>(AABB boundaris);
	MyQuadTree<T>();
	~MyQuadTree<T>();

	bool Insert(Data<T> data);
	void Subdivide();
	void SendDataToChilds();
	std::vector<Data<T>> QueryRange(AABB range);
	
private:

public:
	int capacity = 4;
	AABB boundaris;
	std::vector<Data<T>> objects;
private:
	MyQuadTree<T>* north_west = nullptr;
	MyQuadTree<T>* north_east = nullptr;
	MyQuadTree<T>* south_west = nullptr;
	MyQuadTree<T>* south_east = nullptr;

};


template<class T>
MyQuadTree<T>::MyQuadTree(AABB boundaris):boundaris(boundaris), north_west(nullptr), north_east(nullptr), south_west(nullptr), south_east(nullptr)
{

}
template<class T>
MyQuadTree<T>::MyQuadTree() : north_west(nullptr), north_east(nullptr), south_west(nullptr), south_east(nullptr)
{

}

template <class T>
MyQuadTree<T>::~MyQuadTree()
{
}

template<class T>
bool MyQuadTree<T>::Insert(Data<T> data)
{
	if (boundaris.Contains(data.pos))
		return false;
	
		if (objects.size() < capacity && north_west == nullptr)
		{
			objects.push_back(data);
			return true;
		}

		if(north_west==nullptr)
		{
			Subdivide();
			SendDataToChilds();
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
void MyQuadTree<T>::Subdivide()
{
	float quad_size = boundaris.half_dimension*0.5;

	float2 north_west_quad_pos = float2(boundary.centre.x - quad_size, boundary.centre.y - quad_size);
	north_west = new Quadtree(AABB(north_west_quad_pos, quad_size));

	float2 north_east_quad_pos = float2(boundary.centre.x + quad_size, boundary.centre.y - quad_size);
	north_east = new Quadtree(AABB(north_east_quad_pos, quad_size));

	float2 south_west_quad_pos = float2(boundary.centre.x - quad_size, boundary.centre.y + quad_size);

	south_west = new Quadtree(AABB(south_west_quad_pos, quad_size));

	float2 south_east_quad_pos = float2(boundary.centre.x + quad_size, boundary.centre.y + quad_size);
	south_east = new Quadtree(AABB(south_east_quad_pos, quad_size));
}

template<class T>
inline void MyQuadTree<T>::SendDataToChilds()
{
	std::vector<Data<T>>::iterator it = objects.begin();
	while (it != res.end())
	{
		it = res.erase(it);
		if (north_west->Insert(data))
			return true;
		if (north_east->Insert(data))
			return true;
		if (south_west->Insert(data))
			return true;
		if (south_east->Insert(data))
			return true;
	}
}

template<class T>
std::vector<Data<T>> MyQuadTree<T>::QueryRange(AABB range)
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
