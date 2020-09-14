#include "Board.h"

#include <iostream>

Board::Board(Coord size)
	:width(size.x), height(size.y)
{
	cells = new Cell[width*height];
}

void Board::clear()
{
	memset(cells, Cell::Empty, sizeof(Cell)*width*height);
}
