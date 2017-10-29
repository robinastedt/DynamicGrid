/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#pragma once

#include <vector>

#define DYNAMICGRID_INIT_SIZE 10

template<typename T, size_t N>
class DynamicGrid
{
private:
	std::vector<T> grid;
	inline void padUntil(const uint32_t index);

public:
	DynamicGrid();
	~DynamicGrid();
	/**
	Writes the value of val to the coordinate
	Automatically allocates memory to encompass at least the bounding box determined by the coordinate
	**/
	void put(const int32_t (&coordinate)[N], T val);
	/**
	Returns the value located at the coordinates
	If no value has been put there (T)0 is returned.
	**/
	T get(const int32_t(&coordinate)[N]);
	/**
	Reserves a bounding box stretching at least to the coordinates specified
	If using positive values the negative values are included
	If using negative values the positive edge is not guaranteed to be included
	**/
	void reserve(const int32_t(&coordinate)[N]);
	/**
	Returns a reference to the element at the coordinate
	Observe that the coordinate might not be initialized!
	**/
	T& operator ()(const int32_t(&coordinate)[N]);
};
