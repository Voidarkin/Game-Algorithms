#include "stdafx.h"
#include "DEHRender.h"
#include "pdcwin.h"

// the one and only renderer
DEHRender* DEHRender::instance = NULL;

// lazy access to the instance
DEHRender * DEHRender::getInstance()
{
	if (instance == NULL)
	{
		instance = new DEHRender();
	}
	return instance;
}

// clear screen and configure offset for drawing
void DEHRender::prepareToRender(int x, int y)
{
	offsetX = x;
	offsetY = y;
	clear();
}

// display the offscreen buffer to the user
void DEHRender::doneRendering()
{
	refresh();
}

// draw a C++ string at a location on the screen.
void DEHRender::drawText(int x, int y, std::string text, bool useOffset)
{
	if (useOffset)
	{
		x += offsetX;
		y += offsetY;
	}
	drawText(x, y, text.c_str());
}

// draw a C string at a location on the screen. 
void DEHRender::drawText(int x, int y, const char * text, bool useOffset)
{
	if (useOffset)
	{
		x += offsetX;
		y += offsetY;
	}
	mvprintw(y, x, text);
}

// draw a single character on the screen
void DEHRender::drawChar(int x, int y,char c, bool useOffset)
{
	if (useOffset)
	{
		x += offsetX;
		y += offsetY;
	}
	mvprintw(y, x, "%c",c);
}

// draw the outline of a rectangle on the screen
void DEHRender::drawRect(int x1, int y1, int x2, int y2, char l, bool useOffset)
{
	if (useOffset)
	{
		x1 += offsetX;
		x2 += offsetX;
		y1 += offsetY;
		y2 += offsetY;
	}

	if (x2 <= x1 || y2 <= y1)
	{
		return; // x1,y1 must be above and to the left of x2,y2
	}
	// top & bottom edge
	for (int x = x1; x <= x2; x++)
	{
		if (y1 >= 0 && y1<= 24 && x >=0 &&  x<=79) //clip to screen
			mvprintw(y1, x, "%c",l);
		if (y2 >= 0 && y2 <= 24 && x >= 0 && x <= 79) //clip to screen
			mvprintw(y2, x, "%c", l);
	}
	// left and right edge
	for (int y = y1; y <= y2; y++)
	{
		if (y >= 0 && y <= 24 && x1 >= 0 && x1 <= 79) //clip to screen
			mvprintw(y, x1, "%c", l);
		if (y >= 0 && y <= 24 && x2 >= 0 && x2 <= 79) //clip to screen
			mvprintw(y, x2, "%c", l);
	}
}

// draw a filled in rectagle.  char l is the line, char f is the fill character
void DEHRender::fillRect(int x1, int y1, int x2, int y2, char l, char f, bool useOffset)
{
	if (useOffset)
	{
		x1 += offsetX;
		x2 += offsetX;
		y1 += offsetY;
		y2 += offsetY;
	}

	drawRect(x1, y1, x2, y2, l); // draw the outline first
	// then fill in the interior with the fill character
	for (int x = x1 + 1; x < x2; x++)
	{
		for (int y = y1 + 1; y < y2; y++)
		{
			if (y >= 0 && y <= 24 && x >= 0 && x <= 79) //clip to screen
			mvprintw(y, x, "%c", f);
		}
	}
}

// draw a line from X1 to X2, at height Y1
void DEHRender::drawHLine(int x1, int x2, int y1, char l, bool useOffset)
{
	if (useOffset)
	{
		x1 += offsetX;
		x2 += offsetX;
		y1 += offsetY;

	}


	if (x2 <= x1)
	{
		return; // x1,y1 must be above and to the left of x2,y2
	}
	for (int x = x1; x <= x2; x++)
	{
		if (y1 >= 0 && y1 <= 24 && x >= 0 && x <= 79)//clip to screen
		mvprintw(y1, x, "%c", l);
	}
}

// draw a vertical line from Y1 to Y2, through x1
void DEHRender::drawVLine(int x1, int y1, int y2, char l, bool useOffset)
{
	if (useOffset)
	{
		x1 += offsetX;
		y1 += offsetY;
		y2 += offsetY;
	}


	if (y2 <= y1)
	{
		return; // x1,y1 must be above and to the left of x2,y2
	}
	for (int y = y1; y <= y2; y++)
	{
		if (y >= 0 && y <= 24 && x1 >= 0 && x1 <= 79) //clip to screen
		mvprintw(y, x1, "%c", l);
	}
}


DEHRender::DEHRender()
{
}


DEHRender::~DEHRender()
{
}