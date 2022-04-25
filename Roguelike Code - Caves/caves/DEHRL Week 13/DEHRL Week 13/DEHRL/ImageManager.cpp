#include "stdafx.h"
#include "ImageManager.h"
#include <iostream>
#include <fstream>
// the image manager keeps a cache of images loaded from text files.

ImageManager *ImageManager::instance = NULL;
ImageManager * ImageManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ImageManager();
	}
	return instance;
}

// load a file in, line by line.
std::vector<std::string>* ImageManager::getImage(std::string filename)
{
	// do we already have one
	std::vector<std::string>* result = images[filename];
	if (result == NULL)
	{
		// we need to make a new result, load it in from file, and off we go.
		result = new std::vector<std::string>();
		std::string line;
		// create an input filestram
		std::ifstream inFile(filename);
		// and if we succeeded
		if (inFile.is_open())
		{
			// read in line by line what is in the file
			while (std::getline(inFile, line))
			{
				result->push_back(line);
			}
		}
		// then close things up
		inFile.close();
		images[filename] = result;
	}
	return result;
}

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}