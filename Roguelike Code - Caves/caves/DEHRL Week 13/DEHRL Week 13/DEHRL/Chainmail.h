#pragma once
#include "ArmorDecorator.h"
// armor that gives 5 points of defense. And clanks a lot.  Probably not made from pop can tabs.
class Chainmail :
	public ArmorDecorator
{
public:
	Chainmail(Armor *a);
	virtual ~Chainmail();
	// "Chain Mail"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};