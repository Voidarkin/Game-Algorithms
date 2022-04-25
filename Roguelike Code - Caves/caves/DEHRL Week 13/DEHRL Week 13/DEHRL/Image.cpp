#include "stdafx.h"
#include "Image.h"
#include "ImageManager.h"
#include "DEHRender.h"

// specialized view that shows the contents of a text file
Image::Image()
{
}

Image::~Image()
{
}

// get the image from the image manager.  (it will read it in if it doesn't have it already)
void Image::setImage(std::string filename)
{
	image = ImageManager::getInstance()->getImage(filename);
}

void Image::setPosition(int theX, int theY)
{
	x = theX;
	y = theY;
}

void Image::useOffset(bool use)
{
	usingOffset = use;
}

void Image::render()
{
	for (int i = 0; i < (int)(image->size()); i++)
	{
		std::string s = image->at(i);
		DEHRender::getInstance()->drawText(x, y + i, s, usingOffset);
	}
}

void Image::update(int milliseconds)
{
}