#pragma once
#include "Screen.h"
#include "Model.h"
#include "MouseController.h"
class GameOverScreen :
	public Screen, public Model, public MouseController {
public:
	GameOverScreen();
	virtual ~GameOverScreen();
	// Inherited via Screen
	// returns the splash screen id
	virtual ScreenID getID();
	// add the text view and connect us up as model and controllers
	virtual void initialize();

	// Inherited via Model
	// used to accumulate the time that we're shown before exiting
	virtual void update(int milliseconds) override;

	// from mouse controller
	// if a mouse is clicked, exit
	virtual void leftMouseDown(int x, int y);

private:
	// this is the model data - it's keeping track of the amount of time we've been
	// showing the gameover
	int timeShown;
};