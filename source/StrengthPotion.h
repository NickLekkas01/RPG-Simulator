#ifndef STRENGTHPOTION_H
#define STRENGTHPOTION_H

#include <iostream>
#include "Potion.h"

class StrengthPotion : public Potion {
public:
	StrengthPotion(std::string, uint32_t, uint32_t, itemType,
		uint32_t);

	void print(void) const ;

	virtual void use(uint32_t&, uint32_t&, uint32_t&,
		uint32_t&) const ;

	std::string getStatName(void) const ;
};

#endif
