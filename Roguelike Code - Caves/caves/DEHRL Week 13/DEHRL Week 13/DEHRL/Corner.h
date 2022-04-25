#pragma once
#include "Model.h"
#include "View.h"

// placeholder code for corners (where two hallways meet)
// since we only have one room right now, and no hallways or doors, this is empty code.
// so why have it? So our standard map model has something to interact with.
// when we eventually do have hallways and corners, then that code won't change.
class Corner :
	public Model, public View
{
public:
	Corner();
	virtual ~Corner();
	// draw the corner. - will be in one of 4 directions, depending on which
	// way the L goes
	void render();
	// likely to remain empty.  How often does a corner need to change?
	void update(int milliseconds);
};