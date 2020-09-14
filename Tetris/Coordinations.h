#pragma once

#include <iostream>
#include <string>

using namespace std;

enum Axis
{
	Horizontal,
	Vertical
};

inline Axis other(Axis a) { return (Axis)(1 - a); }

struct Coord
{
	union {
		struct { int x, y; };
		int vals[2];
	};

	Coord() :x(0), y(0) {}
	Coord(int xy) :x(xy), y(xy) {}
	Coord(int x, int y) :x(x), y(y) {}

	inline int& operator[](Axis dir) { return vals[(int)dir]; }

	inline Coord operator+(const Coord& b)const { return Coord(x + b.x, y + b.y); }
};

struct Rect
{
	union {
		struct { int x, y; };
		Coord topLeft;
	};
	union {
		struct { int w, h; };
		Coord size;
	};

	Rect() {}
	Rect(int x, int y, int w, int h) :x(x), y(y), size{ w,h }
	{
	}
};
