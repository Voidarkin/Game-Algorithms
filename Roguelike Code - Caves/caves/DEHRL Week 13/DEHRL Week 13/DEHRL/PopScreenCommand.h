#pragma once
#include "Command.h"
// asks the screen manager to pop the current screen off the stack
class PopScreenCommand :
	public Command
{
public:
	PopScreenCommand();
	virtual ~PopScreenCommand();

	// Inherited via Command
	virtual void execute() override;
};