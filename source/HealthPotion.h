#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include <iostream>
#include <string>
#include "Potion.h"

class HealthPotion : public Potion {
public:
	HealthPotion(std::string, uint32_t, uint32_t, itemType,
		uint32_t) ;

	void print(void) const ;

	void use(uint32_t&, uint32_t&, uint32_t&,
		uint32_t&) const ;

	std::string getStatName(void) const ;
};

#endif
