#pragma once
class Creature;
class AIStrategy
{
public:
	AIStrategy();
	virtual ~AIStrategy();
	virtual int getTargetX() = 0;
	virtual int getTargetY() = 0;
	virtual void dealWithPlayer() = 0;
	void setCreature(Creature *c);
protected:
	Creature *creature;
};