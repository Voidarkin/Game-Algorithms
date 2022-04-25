#pragma once
#include "Point.h"
#include "Model.h"
#include "View.h"
#include <string>
#include <vector>
#include "CreatureObserver.h"
#include "Entity.h"
#include "Component.h"
#include "DamageComponent.h"
#include "ProtectionComponent.h"
#include "CreatureCommandMessageQueue.h"
#include "AIStrategy.h"
// Base class for all creatures
class Creature :
	public Model, public View
{
public:
	Creature();
	virtual ~Creature();
	// Inherited via Model
	// subclasses will override this to move
	virtual void update(int milliseconds);
	// Inherited via View
	// subclasses will override this to draw themselves
	virtual void render();
	// accessors
	void setMaxHP(int mhp);
	int getHP();
	int getMaxHP();
	int getX();
	int getY();
	void setPosition(Point *p);
	Point *getPosition();
	void setPosition(int theX, int theY);
	// move by delta x and delta y
	virtual void move(int dx, int dy);
	// creatures in rooms the player hasn't seen yet are not shown
	// this method makes them visible - and also sets their proxy (which handles
	// drawing active as well)
	virtual void makeVisible();
	// accessors
	void setDamage(int num, int dice);
	void setHitDice(int hd);
	int getHitDice();
	void setAC(int armorClass);
	int getAC();
	void setName(std::string n);
	std::string getName();
	// inflict damage on the creature.  
	// returns true if monster died from this damage
	bool applyDamage(int damage); 
	// can we see the creature
	bool isVisible();
	virtual CreatureType getCreatureType() = 0;
	// add an observer to the list of things we'll notify when we move
	void addObserver(CreatureObserver *observer);
	// stop notifying someone
	void removeObserver(CreatureObserver *observer);
	// send out position updates
	void notifyObservers(EnemyState *state);
	// return all the components from all the equiped items 
	// (and actually any spell effects, hit dice etc)
	Entity *getEquipment();
	CreatureCommandMessageQueue *getQueue();
	void setQueue(CreatureCommandMessageQueue *q);
	AIStrategy* getDefaultStrategy();
	void setStrategy(AIStrategy *theStrategy);
	AIStrategy *getStrategy();
protected:
	// the full display name of the creature
	std::string name;
	// where is the creature
	Point *position;
	// hit points
	int hp;
	// maximum hit points
	int maxHP;
	// armor class
	int ac;
	// how many d8 hit points does it have.  Also used to determine chance to hit player
	int hitDice; // used to compute chance to hit player and hit points
				 // hoe many dice worth of damagedice does an attack inflict?
	int numberOfDamageDice;
	// how big is each damage?
	int damageDice;
	// do we draw and move this creature?
	bool visible;
	// who needs to know when we move?
	std::vector<CreatureObserver *> observers;
	// contains all the current components for the creature.
	Entity * equipment;
	CreatureCommandMessageQueue *queue;
	AIStrategy *defaultStrategy;
	AIStrategy *strategy;
};