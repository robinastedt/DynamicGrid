/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#pragma once
#include "DynamicGrid.h"


// Explicit template instantiation
// Add any types used here

template class DynamicGrid<int, 2>;
template class DynamicGrid<char*, 3>;