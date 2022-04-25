#pragma once
#include "ArmorDecorator.h"
// plus one armor - 5 percent less likelyu to be hit
class PlusOneAD :
	public ArmorDecorator
{
public:
	PlusOneAD(Armor *a);
	virtual ~PlusOneAD();
	// "+1"
	virtual std::string getDescription();
	// Inherited via ArmorDecorator
	virtual Entity * getSubComponents() override;
};