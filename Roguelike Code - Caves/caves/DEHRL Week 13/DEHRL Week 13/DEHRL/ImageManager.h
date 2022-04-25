#pragma once
#include <vector>
#include <string>
#include <map>
// imagemanager holds a cached set of text file contents
class ImageManager
{
public:
	static ImageManager *getInstance();
	// retrieve a set of strings from a file, and cache them. second call with the
	// same filename will return the cached version
	std::vector<std::string> *getImage(std::string filename);
private:
	ImageManager();
	virtual ~ImageManager();
	static ImageManager *instance;
	// the image cache
	std::map<std::string, std::vector<std::string>* > images;
};