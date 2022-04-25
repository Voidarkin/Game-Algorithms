#pragma once
#include "Constants.h"
// Models hold the data and main processing logic
class Model
{
public:
	Model();
	virtual ~Model();
	// abstract method that allows the model to update itself.  milliseconds is the time since the last frame.
	virtual void update(int milliseconds) = 0;
};