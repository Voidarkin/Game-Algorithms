#pragma once
// data structure that stores an x and a Y
class Point
{
public:
	Point();
	virtual ~Point();
	// accessors
	int getX();
	int getY();
	void setPosition(int theX, int theY);
private:
	// the x and y - obviously
	int x;
	int y;
};