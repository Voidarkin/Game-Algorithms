#pragma once
// abstract base class for anything that wants to draw itself on the screen.
class View
{
public:
	View();
	virtual ~View();
	// invoked during the render phase of the game loop.
	virtual void render() = 0;
};