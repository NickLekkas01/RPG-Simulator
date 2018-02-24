#ifndef AGILITYPOTION_H
#define AGILITYPOTION_H

#include <iostream>
#include "Potion.h"

class AgilityPotion : public Potion {
public:
	AgilityPotion(std::string, uint32_t, uint32_t, itemType,
		uint32_t) ;

	void print(void) const ;

	virtual void use(uint32_t&, uint32_t&, uint32_t&,
		uint32_t&) const ;

	std::string getStatName(void) const ;
};

#endif
