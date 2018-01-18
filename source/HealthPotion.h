#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include <iostream>
#include <string>
#include "Potion.h"

class HealthPotion : public Potion {
public:
	HealthPotion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t restoreAmount) :
		Potion(name, pr, min_level, type, restoreAmount)
		{ }

	void print(void) const {
		Potion::print();
		std::cout << "Type: Health Potion" << std::endl;
	}

	void use(uint32_t& healthPower, uint32_t& strength, uint32_t& dexterity,
		uint32_t& agility) const {
		healthPower += restorationAmount;
	}

	std::string getStatName(void) const {
		return "health power";
	}
};

#endif
