
#include <iostream>
#include "StrengthPotion.h"
#include "Potion.h"

StrengthPotion::StrengthPotion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t restoreAmount) :
	Potion(name, pr, min_level, type, restoreAmount)
	{ }

void StrengthPotion::print(void) const {
	Potion::print();
	std::cout << "Type: Strength Potion" << std::endl;
}

void StrengthPotion::use(uint32_t& healthPower, uint32_t& strength, uint32_t& dexterity,
	uint32_t& agility) const {
	strength += restorationAmount;
}

std::string StrengthPotion::getStatName(void) const {
	return "strength";
}
