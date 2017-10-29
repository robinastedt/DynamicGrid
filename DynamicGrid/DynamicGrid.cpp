/*
Author: Robin �stedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#pragma once

#include "DynamicGrid.h"
#include "DynamicGridTypes.h"

// Static helper functions

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

template <size_t N>
static inline uint32_t map(const int32_t(&coordinates)[N]) {
	uint32_t curr_index = negMap(coordinates[0]);
	for (int i = 1; i < N; i++) {
		const uint32_t next_index = negMap(coordinates[1]);
		curr_index = diagMap(curr_index, next_index);
	}
	return curr_index;
}

// Implemenations

template<typename T, size_t N>
DynamicGrid<T,N>::DynamicGrid() : grid(INF2DGRID_INIT_SIZE, 0) { }

template<typename T, size_t N>
DynamicGrid<T,N>::~DynamicGrid() { }

template<typename T, size_t N>
inline void DynamicGrid<T,N>::padUntil(const uint32_t index) {
	if (grid.size() <= index) {
		grid.resize(index + 1, 0);
	}
}

template<typename T, size_t N>
void DynamicGrid<T,N>::put(const int32_t(&coordinates)[N], T val) {
	uint32_t index = map(coordinates);
	padUntil(index);
	grid[index] = val;
}

template<typename T, size_t N>
T DynamicGrid<T,N>::get(const int32_t(&coordinates)[N]) {
	uint32_t index = map(coordinates);
	padUntil(index);
	return grid[index];
}
