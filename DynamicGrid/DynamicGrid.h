/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#pragma once

#include <vector>
#include <assert.h>

#define DYNAMICGRID_INIT_SIZE 10

template<typename T, size_t N>
class DynamicGrid
{
private:
	std::vector<T> grid;
	inline void padUntil(const uint32_t index);
	inline uint32_t map(const int32_t(&coordinate)[N]);
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
	Note: Observe that the coordinate might not be initialized!
	**/
	T& operator ()(const int32_t(&coordinate)[N]);
	


	// Operator overloading and implicit conversion fuckery below..
private:
	/**
	Struct used for holding partial indexing state for operator[]
	**/
	typedef struct PartiallyIndexedDynamicGrid {
		DynamicGrid<T, N>* dyngrid_ptr;
		uint32_t filled;
		int32_t coordinates[N];
		operator T&() {
			assert(filled == N); //tried to reference to lower dimensions than specified
			return dyngrid_ptr->grid[dyngrid_ptr->map(coordinates)];
		}
		T& operator =(T val) {
			assert(filled == N); //Tried assign to lower dimensions than specified
			dyngrid_ptr->grid[dyngrid_ptr->map(coordinates)] = val;
			return *this;
		}
		struct PartiallyIndexedDynamicGrid operator[](int32_t val) {
			assert(filled < N); // Tried to access higher dimensions than specified
			coordinates[filled++] = val;
			return *this;
		}
	} PartiallyIndexedDynamicGrid_t;

public:
	/**
	Use a series of [] calls according to the appropiate amount of dimensions
	Note: If the wrong amount of dimensions are assumed this will fail at runtime!
	Note: Observe that the coordinate might not be initialized!
	**/
	PartiallyIndexedDynamicGrid_t operator[](int32_t val) {
		PartiallyIndexedDynamicGrid_t part;
		part.dyngrid_ptr = this;
		part.filled = 1;
		part.coordinates[0] = val;
		return part;
	}
};
