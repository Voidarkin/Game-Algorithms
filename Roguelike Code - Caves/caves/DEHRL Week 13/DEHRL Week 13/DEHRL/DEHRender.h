#pragma once
#include <string>
// singleton that acts as a front end layer over the PDcurses library
// will have extra methods added to it in the future
class DEHRender
{
public:
	// class method to give access to the renderer
	static DEHRender* getInstance();
	// clear the screeen and set thigns up to draw.  x and y are the offsets to draw at
	void prepareToRender(int x, int y);
	// display the offscreen buffer to the player
	void doneRendering();
	// draw a C++ String on the screen
	void drawText(int x, int y, std::string text, bool useOffset = false);
	// draw an old school C string on the screen
	void drawText(int x, int y, const char * text, bool useOffset = false);
	// draw a single character on the screen
	void drawChar(int x, int y, char c, bool useOffset = false);
	// draw the outline of a rectangle.  BVy default, will use #
	void drawRect(int x1, int y1, int x2, int y2,char l='#', bool useOffset = false);
	// draw a filled in rectangle.  l is the line character, f is the fill character
	void fillRect(int x1, int y1, int x2, int y2, char l = '#', char f = '.', bool useOffset = false);
	// draw a horizontal line.  note that only one y is needed
	void drawHLine(int x1, int y1, int x2, char l = '#', bool useOffset = false);
	// draw a vertical line. note that only one x is needed
	void drawVLine(int x1, int y1, int y2, char l = '#', bool useOffset = false);
private:
	// the one and only renderer
	static DEHRender* instance;
	// constructor and destructor are private to force them to not be callable
	DEHRender();
	virtual ~DEHRender();
	// offsets used to slide things around the screen. Note that this can only be set by prepare to render
	int offsetX;
	int offsetY;
};