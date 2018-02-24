
#include <iostream>
#include "AgilityPotion.h"
#include "Potion.h"


AgilityPotion::AgilityPotion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t restoreAmount) :
	Potion(name, pr, min_level, type, restoreAmount)
	{ }

void AgilityPotion::print(void) const {
	Potion::print();
	std::cout << "Type: Agitliy Potion" << std::endl;
}

void AgilityPotion::use(uint32_t& healthPower, uint32_t& strength, uint32_t& dexterity,
	uint32_t& agility) const {
	agility += restorationAmount;
}

std::string AgilityPotion::getStatName(void) const {
	return "agility";
}
