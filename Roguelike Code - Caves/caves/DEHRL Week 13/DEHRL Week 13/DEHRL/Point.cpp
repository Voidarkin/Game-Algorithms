#include "stdafx.h"
#include "Point.h"

Point::Point()
{
}

Point::~Point()
{
}

// accessor
int Point::getX()
{
	return x;
}

// accessor
int Point::getY()
{
	return y;
}

// accessor
void Point::setPosition(int theX, int theY)
{
	x = theX;
	y = theY;
}