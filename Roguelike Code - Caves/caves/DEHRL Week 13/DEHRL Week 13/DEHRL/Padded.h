#pragma once
#include "ArmorDecorator.h"
// padded armor reduces all damage by 25%, blunt damage specifically by 50%,
// but is bulky, and makes it 5% more likely you'll be hit cause you're wearing
// a couch.
class Padded :
	public ArmorDecorator
{
public:
	Padded(Armor *a);
	virtual ~Padded();
	// "Padded"
	virtual std::string getDescription();
	virtual Entity * getSubComponents() override;
};