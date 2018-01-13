#ifndef POTION_H
#define POTION_H

#include "Item.h"

typedef uint32_t potionType;
namespace potionTypes{
	const uint32_t health = 0;
	const uint32_t strength = 0;
	const uint32_t dexterity = 0;
	const uint32_t agility = 0;
	const char* const potionNames[] = { "Health Potion", "Strength Potion", "Dexterity Potion", "Agility Potion" }; 
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

	void print(void) const {
		Item::print();
		std::cout << "Restoration Amount: " << restorationAmount << std::endl;
		std::cout << potionTypes::potionNames[type] << std::endl;
	}

};

#endif
