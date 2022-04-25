#include "stdafx.h"
#include "Text.h"
#include "DEHRender.h"
// simple text view
Text::Text()
{
}


Text::~Text()
{
}

// string to display
void Text::setText(std::string t)
{
	text = t;
}

// where to display it
void Text::setPosition(int theX, int theY)
{
	x = theX;
	y = theY;
}

// does it move when the camera moves?
void Text::useOffset(bool use)
{
	usingOffset = use;
}

// draw the string
void Text::render()
{
	DEHRender::getInstance()->drawText(x, y, text, usingOffset);
}

// in cvase the text needs to update over time
void Text::update(int milliseconds)
{
}