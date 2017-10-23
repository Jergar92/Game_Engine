#pragma once
#include <vector>
struct QuadPoint
{
	float x = 0;
	float y = 0;
	QuadPoint(float x, float y):x(x),y(y)
	{}

};
struct QuadAABB
{
	QuadPoint centre;
	float half_dimension = 0.0f;
};

template <class T>
struct Data
{
	QuadPoint pos;
	T* data = nullptr;
	Data(QuadPoint pos, T* data) :pos(pos), data(data)
	{}
};
//https://en.wikipedia.org/wiki/Quadtree
//https://codereview.stackexchange.com/questions/84374/quadtree-implementation
template <class T>
class QuadTree
{
public:
	QuadTree<T>();
	~QuadTree<T>();


	
private:

public:
	int capacity = 4;
	QuadAABB boundaris;
	std::vector<Data<T>> objects;
private:
	QuadTree<T>* north_west;
	QuadTree<T>* north_east;
	QuadTree<T>* south_weast;
	QuadTree<T>* south_east;

};

template <class T>
QuadTree<T>::QuadTree()
{
}

template <class T>
QuadTree<T>::~QuadTree()
{
}