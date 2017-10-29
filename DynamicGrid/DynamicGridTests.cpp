/*
Author: Robin Åstedt <robin.astedt@gmail.com>
GitHub: https://github.com/robinastedt/DynamicGrid
*/


#include <iostream>

#include "DynamicGrid.h"

using namespace std;


// For testing purposes
int main(int argc, char** argv) {
	
	DynamicGrid<int,2> grid;
	grid.put({ 0, 0 }, 1);
	grid.put({ 0, 1 }, 2);
	grid.put({ 1, 0 }, 3);
	grid.put({ 1, 1 }, 4);
	grid.put({ 10, 10 }, 5);
	grid.put({ -100, -200 }, 6);
	cout << grid.get({ 0, 0 }) << endl;
	cout << grid.get({ 0, 1 }) << endl;
	cout << grid.get({ 1, 0 }) << endl;
	cout << grid.get({ 1, 1 }) << endl;
	cout << grid.get({ 10, 10 }) << endl;
	cout << grid.get({ -100, -200 }) << endl;

	DynamicGrid<char*, 3> grid2;
	grid2.put({ 1,-3, 4 }, "Text in 3 dimensions!");
	cout << grid2.get({ 1, -3, 4 }) << endl;

	system("pause");
	return EXIT_SUCCESS;
}