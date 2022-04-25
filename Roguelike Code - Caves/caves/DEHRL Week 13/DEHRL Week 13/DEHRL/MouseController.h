#pragma once
// mouse controller is a base class for things that want to know when the mouse
// has moved, or a button has been pressed. the mthods are NOT abstract, since some classes
// may not want to implement them as empty methods, so we do that here.
class MouseController
{
public:
	MouseController();
	virtual ~MouseController();
	// called when the mouse has shifted postion.
	virtual void mouseMoved(int x, int y);
	// callsed when the mouse is being held down in this frame.
	virtual void leftMouseDown(int x, int y);
	// called when the mouse was released in this frame.
	// mouse up will always be preceeded (but maybe not immediately) by a mouse down,
	// unless you are holding the mouse down when the application starts up, and then
	// release it at exactly yhe right time
	virtual void leftMouseUp(int x, int y);
};