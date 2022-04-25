#pragma once
#include "ArmorDecorator.h"
// reduces ice damage by 50%
class ColdproofAD :
	public ArmorDecorator
{
public:
	ColdproofAD(Armor *a);
	virtual ~ColdproofAD();
	// "Coldproof"
	virtual std::string getDescription();
	// Inherited via ArmorDecorator
	virtual Entity * getSubComponents() override;
};