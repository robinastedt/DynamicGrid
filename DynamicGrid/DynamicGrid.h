/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#pragma once

#include <vector>
#include <assert.h>

#define DYNAMICGRID_INIT_SIZE 10
#define DYNAMICGRID_FLAG_DEFAULT 0x00
#define DYNAMICGRID_FLAG_ALLOC_ON_REFERENCE 0x01

template<typename T, size_t N>
class DynamicGrid
{
private:
	std::vector<T> grid;
	uint8_t flags;
	inline void padUntil(const uint32_t index);
	inline uint32_t map(const int32_t(&coordinate)[N]);
public:
	
	DynamicGrid();
	DynamicGrid(uint8_t flags);
	~DynamicGrid();
	/**
	Set option flags
	**/
	void setFlags(uint8_t flags) {
		this->flags = flags;
	}
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
	// TODO: Move implementation to .cpp
private:
	/**
	Struct used for holding partial indexing state for operator[]
	**/
	class PartiallyIndexedDynamicGrid {
	private:
		DynamicGrid<T, N>& dyngrid_ref;
		uint32_t filled;
		int32_t coordinates[N];
	public:
		PartiallyIndexedDynamicGrid(DynamicGrid<T, N>& dyngrid_ref, int32_t first_val) : 
			dyngrid_ref(dyngrid_ref),
			filled(1),
			coordinates{ first_val } { }

		operator T&() {
			assert(filled == N); //tried to reference to lower dimensions than specified
			uint32_t index = dyngrid_ref.map(coordinates);
			if (dyngrid_ref.flags & DYNAMICGRID_FLAG_ALLOC_ON_REFERENCE) {
				dyngrid_ref.padUntil(index);
			}
			return dyngrid_ref.grid[index];
		}
		T& operator =(T val) {
			assert(filled == N); //Tried assign to lower dimensions than specified
			uint32_t index = dyngrid_ref.map(coordinates);
			if (dyngrid_ref.flags & DYNAMICGRID_FLAG_ALLOC_ON_REFERENCE) {
				dyngrid_ref.padUntil(index);
			}
			dyngrid_ref.grid[index] = val;
			return *this;
		}
		PartiallyIndexedDynamicGrid operator[](int32_t val) {
			assert(filled < N); // Tried to access higher dimensions than specified
			coordinates[filled++] = val;
			return *this;
		}
	};



public:
	/**
	Use a series of [] calls according to the appropiate amount of dimensions
	Note: If the wrong amount of dimensions are assumed this will fail at runtime!
	Note: Observe that the coordinate might not be initialized!
	**/
	PartiallyIndexedDynamicGrid operator[](int32_t val) {
		return PartiallyIndexedDynamicGrid(*this, val);
	}
};
