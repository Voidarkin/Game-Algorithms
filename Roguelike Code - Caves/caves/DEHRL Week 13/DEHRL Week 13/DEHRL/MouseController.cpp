#include "stdafx.h"
#include "MouseController.h"

// the methods in here are all empty - they are intended to be replaced in subclasses
// where needed. If you don't need a particular method, don't put it in your subclass, and
// the empty one will be sued instead.

MouseController::MouseController()
{
}


MouseController::~MouseController()
{
}

// empty mehtod here in case subclass doesn't want to both with mouse moved
void MouseController::mouseMoved(int x, int y)
{
}

// empty method here in case subclass doesn't want to deal with mouse down
void MouseController::leftMouseDown(int x, int y)
{
}

// empty method here in case subclass doesn't want to deal with mouse up
void MouseController::leftMouseUp(int x, int y)
{
}