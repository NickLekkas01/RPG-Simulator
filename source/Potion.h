#ifndef POTION_H
#define POTION_H

#include "Item.h"

typedef uint32_t potionType;
namespace potionTypes{
	enum { health, strength, dexterity, agility };
	const char* const potionNames[] = { "Health Potion", "Strength Potion", "Dexterity Potion", "Agility Potion" }; 
}

class Potion : public Item {
private:
	uint32_t restorationAmount;
    potionType type;
public:
	Potion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t restoreAmount, potionType potType, bool avail) :
		Item(name, pr, min_level, type), restorationAmount(restoreAmount),
		type(potType), availability(avail) { }
	uint32_t get_Restoration_amount() const {
		return restorationAmount;
	}
	potionType get_Potion_type() const {
		return type;
	}

	void print(void) const {
		Item::print();
		std::cout << "Restoration Amount: " << restorationAmount << std::endl;
		std::cout << "Availability: " << availability << std::endl;
		std::cout << potionTypes::potionNames[type] << std::endl;
	}

};

#endif
