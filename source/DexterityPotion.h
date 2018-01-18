#ifndef DEXTERITYPOTION_H
#define DEXTERITYPOTION_H

#include <iostream>
#include "Potion.h"

class DexterityPotion : public Potion {
public:
	DexterityPotion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t restoreAmount) :
		Potion(name, pr, min_level, type, restoreAmount)
		{ }

	void print(void) const {
		Potion::print();
		std::cout << "Type: Dexterity Potion" << std::endl;
	}

	virtual void use(uint32_t& healthPower, uint32_t& strength, uint32_t& dexterity,
		uint32_t& agility) const {
		dexterity += restorationAmount;
	}

	std::string getStatName(void) const {
		return "dexterity";
	}
};

#endif
