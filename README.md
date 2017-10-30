# DynamicGrid
Dynamic storage in n dimensions supporting negative coordinates.
Supports automatic memory allocation and both access by value or reference.

## Example usage
	#include <iostream>
	#include "DynamicGrid.h"
	using namespace std;

	int main(int argc, char** argv) {

		DynamicGrid<int, 2> grid;
		// The () and [] syntax does not allocate memory automatically
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
		grid3[10][10][10] = "Yay, dynamic allocation!";
		cout << grid3[10][10][10] << endl;

		system("pause");
		return EXIT_SUCCESS;
	}

