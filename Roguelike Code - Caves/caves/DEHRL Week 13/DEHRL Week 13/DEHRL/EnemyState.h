#pragma once
// Enemy state (whcih looks a lot like a point you can't alter) is used to shuffle
// the location of an enemy in it's own thread to the proxy enemy in the main game
// loop thread
class EnemyState
{
public:
	EnemyState(int theX, int theY);
	virtual ~EnemyState();
	int getX();
	int getY();
private:
	int x;
	int y;
};