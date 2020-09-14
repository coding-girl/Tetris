#include "Board.h"

#include <iostream>

Board::Board(Coord size)
	:width(size.x), height(size.y)
{
	cells = new Cell[width*height];
}

void Board::ClearRow(int row)
{
	memmove(cells + width, cells, sizeof(Cell)*width*(row));
	memset(cells, Cell::Empty, sizeof(Cell)*width);
}

void Board::clear()
{
	memset(cells, Cell::Empty, sizeof(Cell)*width*height);
}
