# DynamicGrid
Dynamic storage in n dimensions supporting negative coordinates

##Example usage:
DynamicGrid<int, 2> grid;
grid.reserve({ 100,200 }); // The () and [] syntax does not allocate memory

grid.put({ 0, 0 }, 1);
grid({ 5, 10 }) = 2;
grid[-100][-200] = 3;

cout << grid.get({ 0, 0 }) << endl; // prints 1
cout << grid({ 5, 10 }) << endl; // print 2
cout << grid[-100][-200] << endl; // prints 3

