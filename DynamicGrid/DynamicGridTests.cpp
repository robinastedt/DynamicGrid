/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/

#include <iostream>
#include "DynamicGrid.h"

using namespace std;

int main(int argc, char** argv) {

	DynamicGrid<int, 2> grid;
	// The () and [] syntax does not allocate memory automatically by default
	grid.reserve({ 100,200 }); 
	
	grid.put({ 0, 0 }, 1);
	grid({ 5, 10 }) = 2;
	grid[-100][-200] = 3;

	cout << grid.get({ 0, 0 }) << endl; // prints 1
	cout << grid({ 5, 10 }) << endl; // print 2
	cout << grid[-100][-200] << endl; // prints 3

	DynamicGrid<char*, 3> grid2;
	grid2.reserve({ 10,10,10 });
	grid2.put({ 1,-3, 4 }, "Text in 3 dimensions!");
	cout << grid2.get({ 1, -3, 4 }) << endl;

	// You can set a flag to let the container dynamically
	// allocate space whenever a coordinate is referenced
	// using () or [] syntax
	DynamicGrid<char*, 3> grid3(DYNAMICGRID_FLAG_ALLOC_ON_REFERENCE);
	grid3[10][10][10] = "Yay, automatic allocation!";
	cout << grid3[10][10][10] << endl;

	// Typically get() returns 0 if trying to access an uninitialized coordiate
	// without allocating any new memory. By setting a flag this behavior can be changed.
	DynamicGrid<int, 2> grid4(DYNAMICGRID_FLAG_ALLOC_ON_GET);
	cout << "grid4 size: " << grid4.containerSize() << endl;
	grid4.get({ 10, 10 });
	cout << "grid4 size: " << grid4.containerSize() << endl;

	system("pause");
	return EXIT_SUCCESS;
}
