#pragma once
#include "View.h"
#include "Player.h"
#include "Model.h"
// the bottom two rows of the screen - displays messages and player info
// no way to hand it messages for now...
// when we do give it that ability, we'll add it as a model, so that we can time out
// messages after a few seconds.
class StatusBar :
	public View, public Model
{
public:
	StatusBar(Player *p);
	virtual ~StatusBar();

	// Inherited from View
	// draw the status bar, and any messages
	virtual void render();
	// second line of status bar - thsi will time out after MESSAGE_TIME milliseconds
	void setMessage(std::string m);

	// Inherited via Model
	virtual void update(int milliseconds) override; private:

private:
	// a pointer to the player, so we can display info from it.
	Player *player;
	// the string to show on the second line
	std::string message;
	// amount of time the second line message has been up.
	int timeMessageHasBeenShown;
};