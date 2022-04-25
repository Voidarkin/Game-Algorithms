#pragma once
// Abstract base class for anything wanting to be told about keypresses
class KeyController
{
public:
	KeyController();
	virtual ~KeyController();
	// subclasses that have this method, and have registered with the DEHGE, will
	// have this method called when a key has been pressed. key contains the keycode.
	virtual void keyPress(int key) = 0;
};