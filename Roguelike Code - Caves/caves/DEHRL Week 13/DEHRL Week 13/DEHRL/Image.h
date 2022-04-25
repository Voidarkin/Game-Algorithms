#pragma once
#include "View.h"
#include "Model.h"
#include <string>
#include <vector>
// view that contains the contents of a text file
class Image :
	public View, public Model
{
public:
	Image();
	virtual ~Image();
	// set the file - this will use the image manager to get the strings, with caching
	void setImage(std::string filename);
	// where doe we want it drawn
	void setPosition(int theX, int theY);
	// keep up with the map
	void useOffset(bool use);
	// Inherited via View
	virtual void render() override;

	// Inherited via Model
	virtual void update(int milliseconds) override;
private:
	int x;
	int y;
	// does render draw these strings with an offset or not
	bool usingOffset = false;
	// the list of strings
	std::vector<std::string> *image;
};