#include "stdafx.h"
#include "EnemyState.h"

// currently resembles a non-updatable point.  We'll send more stuff in here eventually.
EnemyState::EnemyState(int theX, int theY)
{
	x = theX;
	y = theY;
}

EnemyState::~EnemyState()
{
}

// accessor
int EnemyState::getX()
{
	return x;
}

// accessor
int EnemyState::getY()
{
	return y;
}