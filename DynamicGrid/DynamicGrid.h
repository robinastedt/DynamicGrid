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
	void put(const int32_t (&coordinates)[N], T val);
	T get(const int32_t(&coordinates)[N]);
};
