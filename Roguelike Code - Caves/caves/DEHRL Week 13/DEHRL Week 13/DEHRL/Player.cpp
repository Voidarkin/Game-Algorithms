#include "stdafx.h"
#include "Player.h"
#include "Model.h"
#include "View.h"
#include "KeyController.h"
#include "DEHRender.h"
#include "Dungeon.h"
#include "CombatManager.h"
#include "ScreenManager.h"
#include "ItemFactory.h"
#include "Component.h"
#include "Entity.h"
#include "Description.h"
#include "DamageComponent.h"
#include "ProtectionComponent.h"
#include "ItemComponent.h"
#include "HitModComponent.h"
#include "Dagger.h"

// intially, we don't know where the player is.  someone else will hopefully
// call setposition on us soon.
Player::Player()
{
	inventory = new std::vector<Item *>();
	resting = false;
	timeResting = 0;
	position = new Point();
	position->setPosition(0, 0);
	visible = true;
	setName("You");
	setAC(10); // no armor
	setDamage(1, 6);
	setHitDice(1); // used in attack rolls
	setMaxHP(50);
	setupBaseEquipment();
}

Player::~Player()
{
}

// accumulate the total time the player has lived
void Player::update(int milliseconds)
{
	Creature::update(milliseconds); // clean up any outstanding commands
	millisecondsAlive += milliseconds;
	if (resting) // you have to explicitly request to rest using the . command
	{
		timeResting += milliseconds;
		if (timeResting > REST_TIME)
		{
			timeResting = 0;
			if (hp < maxHP)
			{
				hp += 1;
				Dungeon::getInstance()->getStatusBar()->setMessage("You feel better.");
			}
			else
			{
				resting = false;
			}
		}
	}
}

// draw the player at a specific location on the screen.
// we want to use the offset to keep us centered, so make sure the last parameter
// is set to true.
void Player::render()
{
	DEHRender::getInstance()->drawChar(position->getX(), position->getY(), '@', true);
}

// accessor for total time lived - used by status bar currently
long Player::getMillisecondsAlive()
{
	return millisecondsAlive;
}

// award exp to the player.  if they exceed 2000 xp (which needs to be a constant), level them up.
// returns true if the player leveled up this turn.
bool Player::awardXP(int xp)
{
	exp += xp;
	// did we level up?
	if (exp > 2000)
	{
		// yes
		exp -= 2000;
		setHitDice(getHitDice() + 1);
		setMaxHP(getMaxHP() + rand() % 8 + 1);
		// now, modify the hit chance under level
		std::vector<Component *> *levels = equipment->getAllComponentsOfType(ComponentType::LEVEL);
		Entity *level = (Entity *)(levels->at(0));
		level->removeAllComponents(); // remove our old to hit bonus
		HitModComponent *bonus = new HitModComponent(getHitDice());
		level->addComponent(bonus);
		return true;
	}
	return false;
}

// how many xp does the player have? (Used by status bar)
int Player::getXP()
{
	return exp;
}

// try to move the player by a certain amount.  If there is a creature in the way, smack it.
void Player::move(int dx, int dy)
{
	int x = position->getX() + dx;
	int y = position->getY() + dy;
	// is there a creature where we want to move?
	Creature *c = Dungeon::getInstance()->getCurrentMap()->getCreatureAt(x, y);
	// if not, move
	if (c == NULL)
	{
		setPosition(x, y);
		Dungeon::getInstance()->getCurrentMap()->visit(getX(), getY());
	}
	// otherwise, hit it
	else
	{
		CombatManager::getInstance()->processPlayerAttack(c);
	}
}

void Player::addGold(int amount)
{
	gold += amount;
	awardXP(amount);
}

int Player::getGold()
{
	return gold;
}

CreatureType Player::getCreatureType()
{
	return CreatureType::PLAYER;
}

// accessor
void Player::addItem(Item * item)
{
	inventory->push_back(item);
}

// accessor
void Player::dropItem(Item * item)
{
	auto it = std::find(inventory->begin(), inventory->end(), item);
	if (it != inventory->end())
	{
		inventory->erase(it);
	}
}

//. accessor
std::vector<Item*>* Player::getInventory()
{
	return inventory;
}

// we have a body, with a head, and an arm on each side.
void Player::setupBaseEquipment()
{
	equipment = new Entity(ComponentType::PLAYER_ENTITY);
	Entity *head = new Entity(ComponentType::HEAD);
	Entity *body = new Entity(ComponentType::BODY);
	Entity *bodyarmor = new Entity(ComponentType::BODY_ARMOR);
	Entity *leftside = new Entity(ComponentType::LEFT);
	Entity *lefthand = new Entity(ComponentType::HAND);
	Entity *rightside = new Entity(ComponentType::RIGHT);
	Entity *righthand = new Entity(ComponentType::HAND);
	equipment->addComponent(body);
	body->addComponent(head);
	body->addComponent(leftside);
	body->addComponent(rightside);
	body->addComponent(bodyarmor);
	leftside->addComponent(lefthand);
	rightside->addComponent(righthand);
	Description *emptyDescription = new Description("Empty");
	empty = new Entity(ComponentType::EMPTY);
	empty->addComponent(emptyDescription);
	head->addComponent(empty);
	bodyarmor->addComponent(empty);
	lefthand->addComponent(empty);
	righthand->addComponent(empty);
	// also need to add in our hit dice
	Entity *lev = new Entity(ComponentType::LEVEL);
	HitModComponent *bonus = new HitModComponent(1);
	lev->addComponent(bonus);
	equipment->addComponent(lev);
	// and give the player a pointy piece of metal (whick they will need to equip)
	Weapon *w = new Dagger(new Weapon());
	addItem(w);
}

// equip an arbitrary inventory item
void Player::equipItem(Item * item)
{
	// first, is this already equipped? if so, bail
	Entity *root = item->getEntity();
	std::vector<Component *> *items = equipment->getAllComponentsOfType(ComponentType::ITEM_COMPONENT);
	for each (Component *c in (*items))
	{
		ItemComponent *itemC = (ItemComponent *)c;
		if (itemC->getItem() == item)
		{
			// we have a match, so return
			return;
		}
	}
	// made it here, so it's not equipped already.

	// second, we need to figure out what type of item this is.
	// look for weapon or armor components.

	std::vector<Component *> *weaponOrArmor = root->getAllComponentsOfType(ComponentType::WEAPON);
	if (weaponOrArmor->size() == 0) // not a wepon
	{
		weaponOrArmor = root->getAllComponentsOfType(ComponentType::ARMOR);
		if (weaponOrArmor->size() == 0) // not armor either? not equipable.  Might be consumable like a potion or scroll
		{
			return; // failed to equip the item
		}
		else
		{
			equipArmor(item);
		}
	}
	else
	{
		equipWeapon(item);
	}
	// once we are done fiddling with this piece of gear, update our armor class so status bar
	// can show it.
	ac = 10 + CombatManager::getInstance()->getAcBonus(this);
}

// unequip an arbitrary piece of equipment
void Player::unequipItem(Item * item)
{
	bool result = false;
	// check everywhere - we only have 4 spots to look, so can just do this as some if statements.
	std::vector<Component *> *place = equipment->getAllComponentsOfType(BODY_ARMOR);
	if (place->size() != 0)
	{
		// we only have ONE body, so get the list of items out of it.
		Entity *body = (Entity*)(place->at(0));
		result = unequipItem(item, body);
	}
	if (result == false)
	{
		place = equipment->getAllComponentsOfType(HEAD);
		if (place->size() != 0)
		{
			Entity *head = (Entity*)(place->at(0));
			result = unequipItem(item, head);
		}
	}
	if (result == false)
	{
		place = equipment->getAllComponentsOfType(HAND);
		if (place->size() != 0)
		{
			Entity *leftHand = (Entity*)(place->at(0));
			result = unequipItem(item, leftHand);
			if (result == false)
			{
				Entity *rightHand = (Entity*)(place->at(1));
				result = unequipItem(item, rightHand);
			}
		}
	}
	// and again, recalculate the ac
	ac = 10 + CombatManager::getInstance()->getAcBonus(this);
}

// once we know where it is, remove the item from that spot
bool Player::unequipItem(Item * item, Entity * bodypart)
{
	std::vector<Component *> *items = bodypart->getAllComponentsOfType(ComponentType::ITEM_COMPONENT);
	bool found = false;
	if (items->size() != 0)
	{
		ItemComponent *i = (ItemComponent *)(items->at(0));
		if (item == (i->getItem()))
		{
			bodypart->removeAllComponents();
			// we have found it - we need to remove this, and all the rest of the children under this bodypart
			bodypart->addComponent(empty);
			item->setEquipped(false);
			found = true;
		}
	}
	return found;
}

// weapons (and shields) go in an empty hand.  Yes, you can dual wield.
void Player::equipWeapon(Item * item)
{
	// is there a hand to wield this with? (Will allow dual wielding for now)
	// get all the hands, then look for empty spaces
	std::vector<Component *> *hands = equipment->getAllComponentsOfType(ComponentType::HAND);
	std::vector<Component *> *empty = NULL;
	for each (Component *hand in (*hands))
	{
		// does it have an empty component?
		empty = hand->getAllComponentsOfType(ComponentType::EMPTY);
		if (empty->size() == 0)
		{
			continue; // this hand is already occupied
		}
		else
		{
			// we need to add the rest of the components to the empty hand
			// happily, this is trivial.
			((Entity *)(hand))->removeAllComponents(); // get rid of the emptiness
			((Entity *)(hand))->addComponent(item->getEntity()); // and replace it with a weapon
			item->setEquipped(true);
			break;
			// of course, this depends on the entity that is retrieved from the item being populated with everything from
			// any and all decorators that are part of the weapon.  This is getEntity's problem though.
		}
	}
}

// not that we have any helms, but if they player wants to equip one, they can.
void Player::equipHelm(Item * item)
{
	// is there a head to wear this?
	// get all the heads, then look for empty spaces
	std::vector<Component *> *heads = equipment->getAllComponentsOfType(ComponentType::HEAD);
	std::vector<Component *> *empty = NULL;
	// if you want the player to have more than one head, add a second one when setting up the equipment.
	// Zaphod is a potential player character after all...
	for each (Component *head in (*heads)) // well, maybe the player HAS two heads...
	{
		// does it have an empty component?
		empty = head->getAllComponentsOfType(ComponentType::EMPTY);
		if (empty->size() == 0)
		{
			continue; // this head is already occupied
		}
		else
		{
			// we need to add the rest of the components to the empty head
			// happily, this is trivial.
			((Entity *)(head))->removeAllComponents(); // get rid of the emptiness
			((Entity *)(head))->addComponent(item->getEntity()); // and replace it with a Helm
			item->setEquipped(true);
			break;
			// of course, this depends on the entity that is retrieved from the item being populated with everything from
			// any and all decorators that are part of the weapon.  This is getEntity's problem though.
		}
	}
}

// stuff that protects the torso.
void Player::equipBodyArmor(Item * item)
{
	// is there a body to wear this?
	// get all the bodies, then look for empty spaces
	std::vector<Component *> *bodies = equipment->getAllComponentsOfType(ComponentType::BODY_ARMOR);
	std::vector<Component *> *empty = NULL;
	for each (Component *body in (*bodies)) // well, maybe the player HAS two bodiess...
	{
		// does it have an empty component?
		empty = body->getAllComponentsOfType(ComponentType::EMPTY);
		if (empty->size() == 0)
		{
			continue; // this body is already occupied
		}
		else
		{
			// we need to add the rest of the components to the empty body
			// happily, this is trivial.
			((Entity *)(body))->removeAllComponents(); // get rid of the emptiness
			((Entity *)(body))->addComponent(item->getEntity()); // and replace it with the armor
			item->setEquipped(true);
			break;
			// of course, this depends on the entity that is retrieved from the item being populated with everything from
			// any and all decorators that are part of the weapon.  This is getEntity's problem though.
		}
	}
}

// by this point, you should realize that we should replace all those equip foo type methods with
// one method that takes what type of thing we're trying to equip over as a paramter. maybe by next
// week...

// player picked a piece of armor
void Player::equipArmor(Item * item)
{
	// is this item already equipped?
	// where can this armor go? 
	// helms go on heads.
	// shields go on hands
	// armor goes on body
	Entity *root = item->getEntity();
	std::vector<Component *> *helm = root->getAllComponentsOfType(ComponentType::HELM);
	if (helm->size() != 0)
	{
		equipHelm(item);
		return;
	}
	std::vector<Component *> *shield = root->getAllComponentsOfType(ComponentType::SHIELD);
	if (shield->size() != 0)
	{
		equipWeapon(item); // Shields go in hands, just like weapons do...
		return;
	}
	std::vector<Component *> *body = root->getAllComponentsOfType(ComponentType::BODY_ARMOR);
	if (body->size() != 0)
	{
		equipBodyArmor(item);
	}
}