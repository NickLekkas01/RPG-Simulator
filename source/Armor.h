#ifndef ARMOR_H
#define ARMOR_H

#include <iostream>
#include "Item.h"

class Armor : public Item {
private:
	uint32_t armorValue;
public:
	Armor(std::string, uint32_t, uint32_t, itemType, uint32_t);

	uint32_t getArmor();
	void resetArmor(uint32_t) ;
	void resetArmor() ;
	void decreaseArmor(uint32_t);

	void print() const;
};

#endif
