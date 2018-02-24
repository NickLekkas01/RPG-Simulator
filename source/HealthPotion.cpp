
#include <iostream>
#include <string>
#include "HealthPotion.h"
#include "Potion.h"


HealthPotion::HealthPotion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t restoreAmount) :
	Potion(name, pr, min_level, type, restoreAmount)
	{ }

void HealthPotion::print(void) const {
	Potion::print();
	std::cout << "Type: Health Potion" << std::endl;
}

void HealthPotion::use(uint32_t& healthPower, uint32_t& strength, uint32_t& dexterity,
	uint32_t& agility) const {
	healthPower += restorationAmount;
}

std::string HealthPotion::getStatName(void) const {
	return "health power";
}


