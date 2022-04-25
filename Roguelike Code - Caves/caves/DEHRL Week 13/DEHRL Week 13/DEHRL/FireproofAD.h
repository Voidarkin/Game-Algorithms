#pragma once
#include "ArmorDecorator.h"
// fireproof reduces damage from fire by 50%
class FireproofAD :
	public ArmorDecorator
{
public:
	// we need to decorate something
	FireproofAD(Armor *a);
	virtual ~FireproofAD();
	// "Fireproof"
	virtual std::string getDescription();
	// Inherited via ArmorDecorator
	virtual Entity * getSubComponents() override;
};