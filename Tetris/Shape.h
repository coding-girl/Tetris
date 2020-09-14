#pragma once

#include "Coordinates.h"

class Shape
{
	char cells[4][4];

public:
	Shape(const char* line0, const char* line1, const char* line2, const char* line3);

	static const Shape* GetRandomShape();

	bool IsSolid(Coord, int rot) const;
};

