/*
Author: Robin Åstedt <robin.astedt@gmail.com>
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
static uint32_t map(const int32_t(&coordinates)[N]) {
	uint32_t curr_index = negMap(coordinates[0]);
	for (int i = 1; i < N; i++) {
		const uint32_t next_index = negMap(coordinates[1]);
		const uint32_t sum = curr_index + next_index;
		const uint32_t offset = sum * (sum + 1) / 2;
		curr_index = offset + curr_index;
	}
	return curr_index;
}

// Implemenations

template<typename T, size_t N>
DynamicGrid<T,N>::DynamicGrid() : grid(10, 0) { }

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

/*
template<class T>
void Inf2dGrid<T>::put(const int32_t x, const int32_t y, const T val) {
	uint32_t index = map(x, y);
	padUntil(index);
	grid[index] = val;
}

template<class T>
T Inf2dGrid<T>::get(const int x, const int y) {
	uint32_t index = map(x, y);
	padUntil(index);
	return grid[index];
}
*/
