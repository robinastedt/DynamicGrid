/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#include <assert.h>
#include <cstdint>
#include <cstdlib>
#include "DynamicGrid.h"
#include "DynamicGridTypes.h"


// Implemenations

static inline uint32_t negMap(const int32_t a) {
	//Alternate negative and positive indices
	return (a < 0) ? (-a * 2) - 1 : a * 2;
}

static inline uint32_t diagMap(const uint32_t a1, const uint32_t a2) {
	//diagonal offset
	const uint32_t sum = a1 + a2;

	//algebraic sum results in 1d offset
	const uint32_t offset = sum * (sum + 1) / 2;

	//The a1 coordinate denotes the position in the diagonal row/column
	const uint32_t index = offset + a1;

	return index;
}

template<typename T, size_t N>
inline uint32_t DynamicGrid<T, N>::map(const int32_t(&coordinate)[N]) {
	uint32_t curr_index = negMap(coordinate[0]);
	for (int i = 1; i < N; i++) {
		const uint32_t next_index = negMap(coordinate[1]);
		curr_index = diagMap(curr_index, next_index);
	}
	return curr_index;
}

template<typename T, size_t N>
DynamicGrid<T,N>::DynamicGrid() :
	grid(DYNAMICGRID_INIT_SIZE, 0),
	flags(DYNAMICGRID_FLAG_DEFAULT) { 
	assert(N > 0);
}

template<typename T, size_t N>
DynamicGrid<T, N>::DynamicGrid(uint8_t flags) :
	grid(DYNAMICGRID_INIT_SIZE, 0),
	flags(flags) {
	assert(N > 0);
}

template<typename T, size_t N>
DynamicGrid<T,N>::~DynamicGrid() { }

template<typename T, size_t N>
inline void DynamicGrid<T,N>::padUntil(const uint32_t index) {
	if (grid.size() <= index) {
		grid.resize(index + 1, 0);
	}
}

template<typename T, size_t N>
void DynamicGrid<T,N>::put(const int32_t(&coordinate)[N], T val) {
	const uint32_t index = map(coordinate);
	padUntil(index);
	grid[index] = val;
}

template<typename T, size_t N>
T DynamicGrid<T,N>::get(const int32_t(&coordinate)[N]) {
	const uint32_t index = map(coordinate);
	if (flags & DYNAMICGRID_FLAG_ALLOC_ON_GET) {
		padUntil(index);
		return grid[index];
	}
	else {
		return grid.size() < index ? (T)0 : grid[index];
	}
}

template<typename T, size_t N>
void DynamicGrid<T, N>::reserve(const int32_t(&coordinate)[N]) {
	padUntil(map(coordinate));
}

template<typename T, size_t N>
T& DynamicGrid <T, N>::operator()(const int32_t(&coordinate)[N]) {
	const uint32_t index = map(coordinate);
	if (flags & DYNAMICGRID_FLAG_ALLOC_ON_REFERENCE) {
		padUntil(index);
	}
	return grid[index];
}

template<typename T, size_t N>
size_t DynamicGrid <T, N>::containerSize() {
	return grid.size() * sizeof(T);
}
