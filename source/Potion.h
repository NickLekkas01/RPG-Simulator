#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include <string>

typedef uint32_t potionType;
namespace potionTypes{
	const uint32_t health = 0;
	const uint32_t strength = 1;
	const uint32_t dexterity = 2;
	const uint32_t agility = 3;
	const char* const potionNames[] = { "Health Potion", "Strength Potion", "Dexterity Potion", "Agility Potion" }; 
	const char* const statNames[] = { "health", "strength", "dexterity", "agility" }; 
}

class Potion : public Item {
private:
	uint32_t restorationAmount;
    potionType type;
public:
	Potion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t restoreAmount, potionType potType) :
		Item(name, pr, min_level, type), restorationAmount(restoreAmount),
		type(potType) { }

	uint32_t getRestorationAmount() const {
		return restorationAmount;
	}
	potionType getPotionType() const {
		return type;
	}

	std::string getStatName(void) const {
		return potionTypes::statNames[type];
	}

	void print(void) const {
		Item::print();
		std::cout << "Restoration Amount: " << restorationAmount << std::endl;
		std::cout << potionTypes::potionNames[type] << std::endl;
	}

};

#endif
