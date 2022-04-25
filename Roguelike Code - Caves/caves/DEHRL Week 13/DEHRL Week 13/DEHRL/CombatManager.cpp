#include "stdafx.h"
#include "CombatManager.h"
#include <sstream>
#include "ScreenManager.h"
#include "ACModComponent.h"
#include "HitModComponent.h"
#include <map>
CombatManager* CombatManager::instance = NULL;

// lazy access to the instance
CombatManager * CombatManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new CombatManager();
	}
	return instance;
}

// handle a player attack on a given creature
void CombatManager::processPlayerAttack(Creature * c)
{
	// get the details we need to process the attack
	Player *p = Dungeon::getInstance()->getPlayer();
	int cAC = 10 + getAcBonus(c);
	int hitBonus = getHitBonus(p);
	// did this attack hit?
	bool didYouHit = rollToHit(hitBonus, cAC);
	std::stringstream s;
	s << p->getName() << " attack the " << c->getName();
	if (didYouHit) // yes
	{
		int damage = rollForDamage(p, c);
		bool didItDie = c->applyDamage(damage);
		if (didItDie)
		{
			// need to remove the creature from the game.
			//Dungeon::getInstance()->getCurrentMap()->removeCreature(c);
			s << " and hit for " << damage << " damage, killing it.";
			// and award exp - 10 xp per monster hp
			if (p->awardXP(c->getMaxHP() * 10))
			{
				s << " You leveled up.";
			}
		}
		else // it's still alive
		{
			s << " and hit for " << damage << " damage.";
		}
	}
	else // no, you missed this round
	{
		s << " and missed.";
	}
	Dungeon::getInstance()->getStatusBar()->setMessage(s.str());

}

// process a creature attacking the player
void CombatManager::processCreatureAttack(Creature * c)
{
	// get details we need to process the attack
	Player *p = Dungeon::getInstance()->getPlayer();
	int pAC = 10 + getAcBonus(p);
	int hitBonus = getHitBonus(c);
	// swing at the player
	bool didYouHit = rollToHit(hitBonus, pAC);
	std::stringstream s;
	s << c->getName() << " attacked " << p->getName();
	if (didYouHit)
	{
		int damage = rollForDamage(c,p);
		bool didItDie = p->applyDamage(damage);
		if (didItDie)
		{
			// need to remove the player from the game.
			s << " and hit for " << damage << " damage, killing you.";
			// need to go to the game over screen...
			ScreenManager::getInstance()->setScreen(ScreenID::GAME_OVER_SCREEN);
		}
		else
		{
			s << " and hit for " << damage << " damage.";
		}
	}
	else
	{
		s << " and missed.";
	}
	Dungeon::getInstance()->getStatusBar()->setMessage(s.str());
}

// get all the ac bits from the creature
int CombatManager::getAcBonus(Creature * c)
{
	std::vector<Component *> *acBonus = c->getEquipment()->getAllComponentsOfType(ComponentType::AC_MOD);
	int result = 0;
	for each (Component *com in (*acBonus))
	{
		ACModComponent *mod = (ACModComponent *)com;
		result += mod->getACModification();
	}
	return result;
}

// get all the hit bonuses (hit dice, +1 weapons etc) from the creature
int CombatManager::getHitBonus(Creature * c)
{
	std::vector<Component *> *hitBonus = c->getEquipment()->getAllComponentsOfType(ComponentType::HIT_MOD);
	int result = 0;
	for each (Component *com in (*hitBonus))
	{
		HitModComponent *mod = (HitModComponent *)com;
		result += mod->getHitModification();
	}
	return result;
}

// determine damage, then mitigate it with defenses.
int CombatManager::rollForDamage(Creature * attacker, Creature * defender)
{
	int result = 0;
	std::map<DamageType, int> damageMap;
	std::vector<Component *> *damages = attacker->getEquipment()->getAllComponentsOfType(ComponentType::DAMAGE);
	for each (Component *c in (*damages))
	{
		DamageComponent *d = (DamageComponent *)c;
		int& val = damageMap[d->getDamageType()];
		val += d->rollDamage();
	}
	// at this point, we have a nice mapping of what we want to try to inflict.  now we need to stop it.
	// so do what we did above, but for protection instead
	std::map<DamageType, float> protectionMap;
	std::vector<Component *> *protections = defender->getEquipment()->getAllComponentsOfType(ComponentType::PROTECTION);
	for each (Component *c in (*protections))
	{
		ProtectionComponent *p = (ProtectionComponent *)c;
		float& val = protectionMap[p->getProtectionType()];
		val += p->getProtectionFactor();
	}

	// ok - we've got all out base damage and protection values
	// loop over all the damage, and look to see if there is a matching defense factor. if so, drop it.
	// at the end, if we have a protection for any, reduce result by that much.
	for (std::map<DamageType, int>::iterator it = damageMap.begin(); it != damageMap.end(); ++it)
	{
		int damageVal = it->second;
		float& protectVal = protectionMap[it->first]; // how much do we reduce damage by?
		if (protectVal > 1.0f)
		{
			damageVal = 0;
		}
		else if (protectVal >=0.0f)
		{
			damageVal = (int)(damageVal* (1.0f - protectVal));
		}
		else // we actually take more damage from this.
		{
			protectVal *= -1;
			damageVal = (int)(damageVal*(1 + protectVal));
		}
		result += damageVal;
	}

	// now if they have protection from anything, apply that
	float &anyVal = protectionMap[DamageType::ANY];
	if (anyVal > 1.0f)
	{
		result = 0;
	}
	else if (anyVal >= 0.0f)
	{
		result = (int)(result *(1.0 - anyVal));
	}
	else // we actually take more damage from this.
	{
		anyVal *= -1;
		result =(int)(result * (1 + anyVal));
	}
	return result;
}

CombatManager::CombatManager()
{
}


CombatManager::~CombatManager()
{
}

// old school D&D rules.  d20 to attack.  20 always hits, 1 always misses
bool CombatManager::rollToHit(int hitBonus, int ac)
{
	int d20 = rand() % 20 + 1;
	if (d20 == 1)
	{
		return false; // 1 always missed
	}
	if (d20 == 20)
	{
		return true; // 20 always hits
	}
	// now it gets trickier
	int thaco = 21 - hitBonus; // thaco - to hit ac zero
	int neededToHit = thaco - ac; // if we need a 15 to hit ac zero, and you have ac 10, then we need a 5
	if (d20 >= neededToHit)
	{
		return true;
	}
	return false;
}