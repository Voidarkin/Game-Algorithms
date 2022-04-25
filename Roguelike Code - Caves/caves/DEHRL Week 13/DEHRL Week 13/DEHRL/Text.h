#pragma once
#include "View.h"
#include "Model.h"
#include <string>
// helper class that acts as a single view with a string stored in it's model.
// if useoffset is true, it will scroll around the screen.  if not, it's in a fixed location
class Text :
	public View, public Model
{
public:
	Text();
	virtual ~Text();
	// set up the string this view will display
	void setText(std::string t);
	// where will it be displayed
	void setPosition(int theX, int theY);
	// should it be in a fixed position or not
	void useOffset(bool use);
	// Inherited via View
	// draw the string on the screen
	virtual void render();
	// Inherited via Model
	// update the text.  a subclass of this view might use this to animate the string text
	virtual void update(int milliseconds);
private:
	// the string to show
	std::string text;
	// location of the string on the screen
	int x;
	int y;
	// does render draw this string with an offset or not
	bool usingOffset = false;
};