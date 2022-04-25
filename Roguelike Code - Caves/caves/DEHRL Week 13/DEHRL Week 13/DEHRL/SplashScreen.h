#pragma once
#include "Screen.h"
#include "Model.h"
#include "KeyController.h"
#include "MouseController.h"
// the splash screen.
// we need to be a key controller and mouse controller, so we can go away with a keystroke
// or a mouse click, and a model, so we get elapsed time so we'll time out after a given
// amount of time as well.
// displays a single message on the screen for at most 5 seconds, then pushes the main menu screen

class SplashScreen :
	public Screen, public Model, public KeyController, public MouseController
{
public:
	SplashScreen();
	virtual ~SplashScreen();

	// Inherited via Screen
	// returns the splash screen id
	virtual ScreenID getID();
	// add the text view and connect us up as model and controllers
	virtual void initialize();

	// Inherited via Model
	// used to accumulate the time that we're shown before switching to the main menu
	virtual void update(int milliseconds) override;

	// Inherited via KeyController
	// waits for any key to be pressed, then goes to the main menu
	virtual void keyPress(int key) override;

	// from mouse controller
	// if a mouse is clicked, go to the main menu
	virtual void leftMouseDown(int x, int y);

private:
	// this is the model data - it's keeping track of the amount of time we've been
	// showing the splash screen
	int timeShown;
};