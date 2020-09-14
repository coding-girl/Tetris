#include "Shape.h"

Shape::Shape(const char* line0, const char* line1, const char* line2, const char* line3)
{
	memcpy(cells[0], line0, 4);
	memcpy(cells[1], line1, 4);
	memcpy(cells[2], line2, 4);
	memcpy(cells[3], line3, 4);
}

bool Shape::IsSolid(Coord pt, int rot)const
{
	while (rot-- > 0)
		pt = Coord(pt.y, 3 - pt.x);

	return cells[pt.y][pt.x] != ' ';
}



const Shape AllShapes[] = {
	Shape("  . ",
		  " ...",
		  "    ",
		  "    "),
		  
	Shape("  . ",
		  "  . ",
		  " .. ",
		  "    "),


	Shape(" .  ",
		  " .  ",
		  " .. ",
		  "    "),


	Shape("  . ",
		  "  . ",
		  "  .  ",
		  "  .  "),


	Shape(" .. ",
		  " .. ",
		  "    ",
		  "    "),

    Shape(" .. ",
		  "  ..",
		  "    ",
		  "    "),

	Shape(" .. ",
		  "..  ",
		  "    ",
		  "    "),

};

const Shape* Shape::GetRandomShape()
{
	return &AllShapes[rand() % 7];
}
