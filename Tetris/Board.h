#pragma once

#include "Coordinates.h"

enum Cell
{
	Empty,
	Filled
};

class Board
{
private:
	int width;
	int height;
	Cell* cells;

public:
	Board(Coord size);


	inline int get_width() { return width; }
	inline int get_height() { return height; }

	void ClearRow(int row);
	void clear();

	inline Cell& operator[](const Coord& c) { return get_cell(c); }

	inline Cell& get_cell(int x, int y) { return cells[y*width + x]; }
	inline Cell& get_cell(Coord coord) { return get_cell(coord.x, coord.y); }

	inline bool is_empty(int x, int y) { return get_cell(x, y) == Cell::Empty; }
	inline bool is_empty(Coord coord) { return get_cell(coord) == Cell::Empty; }
};

