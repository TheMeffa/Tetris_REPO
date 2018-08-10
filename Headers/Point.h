
#include "Constants.h"
#pragma once
class Point
{
public:
	int x;
	int y;

	Point(int _x = 0, int _y = 0, PointType _pt = EMPTY_FIELD);
	PointType pt;
	bool operator == (Point p);
	
	void setAll(int _x, int _y, PointType _pt);

};
