#ifndef ARMOR_H
#define ARMOR_H

#include <iostream>
#include "Item.h"

class Armor : public Item {
private:
	uint32_t armorValue;
public:
	Armor(std::string name, uint32_t price, uint32_t min_level, itemType type, uint32_t value) : Item(name, price, min_level, type), armorValue(value) {}

	uint32_t getArmor(){
		return armorValue;
	}
	void resetArmor(uint32_t value = 0) {
		armorValue = value;
	}
	void decreaseArmor(uint32_t num){
		armorValue-=num;
	}

	void print() const {
		Item::print();
		std::cout << "Armor: " << armorValue << std::endl;
	}
};

#endif
