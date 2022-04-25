#pragma once
#include "Enemy.h"
// a special type of enemies - bats flit around randomly.
// if the are next to the player, they will attack one, then flit off again.
class Bat :
	public Enemy
{
public:
	Bat();
	virtual ~Bat();
	// override to give different movement behaviour
	virtual void update(int milliseconds);
private:
	// the target x and y that the bat wants to move to
	int tx;
	int ty;
	// how many more times will it try to get to that location
	int remainingMoves;
	// bat will only attack once if next to player, then will force a move
	bool attackedAlready;
};