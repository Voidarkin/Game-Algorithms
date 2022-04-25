#include "stdafx.h"
#include "Bat.h"
#include "Dungeon.h"
// Bat is a specialed subclass of creature with different move capabilites
Bat::Bat()
{
	// where we want to go
	tx = 0;
	ty = 0;
	// how long until we change our mind
	remainingMoves = 0;
	// did we already attack
	attackedAlready = false;
}

Bat::~Bat()
{
}

// flit around by picking a target, and heading in that general direction for a bit,
// them picking a new target.
void Bat::update(int milliseconds)
{
	if (!visible) // not active, do nothing
	{
		return;
	}
	// bats move around semi-randomly
	if (remainingMoves <= 0) // if we used up all the moves, then pick a new target
	{
		remainingMoves = rand() % 10;
		// tx and ty are the target x and y we want to try to get to.
		// if they lead us into a wall, we'll just sit there... 
		tx = getX() + rand() % 11 - 5;
		ty = getY() + rand() % 11 - 5;
	}
	remainingMoves--;
	// Where is the player, relative to us? (calculate dx and dy)
	int px = Dungeon::getInstance()->getPlayer()->getX();
	int py = Dungeon::getInstance()->getPlayer()->getY();
	int dx = px - position->getX();
	int dy = py - position->getY();

	// if we are next to the player, and didn't just try to bit it, then
	// attack
	if ((dx*dx + dy*dy) == 1 && attackedAlready == false)
	{
		attackPlayer();
		attackedAlready = true;
	}
	else // otherwise, move and clear the fact that we tried to attack
	{
		moveTo(tx, ty);
		attackedAlready = true;
	}
}