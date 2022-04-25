#pragma once
#include "Command.h"
#include "Constants.h"
// requests that the screen manager push a screen onto the stack
class PushScreenCommand :
	public Command
{
public:
	PushScreenCommand();
	virtual ~PushScreenCommand();

	// Inherited via Command
	virtual void execute() override;
	// which screen must go on the stack
	void setScreenID(ScreenID id);
private:
	ScreenID screenID;
};