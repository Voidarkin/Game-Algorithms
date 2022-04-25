#pragma once
#include "AIStrategy.h"
class BatAIStrategy :
	public AIStrategy
{
public:
	BatAIStrategy();
	~BatAIStrategy();

	// Inherited via AIStrategy
	virtual void dealWithPlayer() override;
private:
	// the target x and y that the bat wants to move to
	int tx;
	int ty;
	// how many more times will it try to get to that location
	int remainingMovesX;
	int remainingMovesY;
	// bat will only attack once if next to player, then will force a move
	bool attackedAlready;

	// Inherited via AIStrategy
	virtual int getTargetX() override;
	virtual int getTargetY() override;
};

