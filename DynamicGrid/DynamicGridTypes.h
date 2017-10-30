/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#ifndef _DYNAMIC_GRID_TYPES_
#define _DYNAMIC_GRID_TYPES_
#include "DynamicGrid.h"


// Explicit template instantiation
// Add any types used here

template class DynamicGrid<int, 2>;
template class DynamicGrid<char*, 3>;

#endif
