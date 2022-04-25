#pragma once
#include "Player.h"
#include "Creature.h"
#include "Dungeon.h"
// Combat Manager is a singleton that handles creature -> player or
// player -> creature combat
class CombatManager
{
public:
	static CombatManager *getInstance();
	// deal with the player attacking a creature
	void processPlayerAttack(Creature *c);
	// deal with a creature attacking a creature
	void processCreatureAttack(Creature *c);
	int getAcBonus(Creature *c);
	int getHitBonus(Creature *c);
	int rollForDamage(Creature *attacker, Creature *defender);
private:
	static CombatManager *instance;
	CombatManager();
	virtual ~CombatManager();
	// take a swing at an armor class from a certain power level of creature (or player)
	bool rollToHit(int hitdice, int ac);
};