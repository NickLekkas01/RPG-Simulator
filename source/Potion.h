#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include <string>

class Potion : public Item {
protected:
	uint32_t restorationAmount;
public:
	Potion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t restoreAmount) :
		Item(name, pr, min_level, type), restorationAmount(restoreAmount)
		{ }

	uint32_t getRestorationAmount() const {
		return restorationAmount;
	}

	virtual void print(void) const {
		Item::print();
		std::cout << "Restoration Amount: " << restorationAmount << std::endl;
	}
	
	virtual void use(uint32_t& healthPower, uint32_t& strength, uint32_t& dexterity,
		uint32_t& agility) const = 0;

	virtual std::string getStatName(void) const = 0;
};

#endif
