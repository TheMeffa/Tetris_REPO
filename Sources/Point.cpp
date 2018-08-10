#include "Point.h"


Point::Point(int _x, int _y, PointType _pt) : x(_x), y(_y), pt(_pt){}

bool Point :: operator== (Point p)
{
	if (x == p.x && y == p.y)
		return true;
	else return false;
}

void Point::setAll(int _x, int _y, PointType _pt)
{
	x = _x;
	y = _y;
	pt = _pt;
}