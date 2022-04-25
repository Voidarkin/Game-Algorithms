#pragma once
#include "Command.h"
// ask the game engine to shutdown
class QuitCommand :
	public Command
{
public:
	QuitCommand();
	virtual ~QuitCommand();

	// Inherited via Command
	virtual void execute() override;
};