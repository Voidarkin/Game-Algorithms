#pragma once
#include "ArmorDecorator.h"
// stadnard tin can armor. gives -8 to ac.
class Platemail :
	public ArmorDecorator
{
public:
	Platemail(Armor *a);
	virtual ~Platemail();
	// "Plate Mail"
	virtual std::string getDescription();
	virtual Entity *getSubComponents();
};