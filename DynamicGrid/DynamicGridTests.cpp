/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/


#include <iostream>

#include "DynamicGrid.h"

using namespace std;


// For testing purposes
int main(int argc, char** argv) {

	DynamicGrid<int, 2> grid;
	grid.reserve({ 100,200 });

	grid.put({ 0, 0 }, 1);
	grid({ 5, 10 }) = 2;
	grid[-100][-200] = 3;

	cout << grid.get({ 0, 0 }) << endl;
	cout << grid({ 5, 10 }) << endl;
	cout << grid[-100][-200] << endl;

	DynamicGrid<char*, 3> grid2;
	grid2.reserve({ 10,10,10 });
	grid2.put({ 1,-3, 4 }, "Text in 3 dimensions!");
	cout << grid2.get({ 1, -3, 4 }) << endl;



	system("pause");
	return EXIT_SUCCESS;
}