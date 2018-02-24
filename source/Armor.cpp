
#include <iostream>
#include "Armor.h"
#include "Item.h"


Armor::Armor(std::string name, uint32_t price, uint32_t min_level, itemType type, uint32_t value) : Item(name, price, min_level, type), armorValue(value) {}

uint32_t Armor::getArmor(){
	return armorValue;
}
void Armor::resetArmor() {
    resetArmor(0);
}
void Armor::resetArmor(uint32_t value) {
	armorValue = value;
}
void Armor::decreaseArmor(uint32_t num){
	armorValue-=num;
}

void Armor::print() const {
	Item::print();
	std::cout << "Armor: " << armorValue << std::endl;
}

