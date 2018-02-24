
#include <iostream>
#include <cstdint>
#include "Weapon.h"
#include "Item.h"


Weapon::Weapon(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t dmg, uint32_t h) :
	Item(nam, pr, min_level, type), damage(dmg), hands(h) { }

Weapon::Weapon(const class Weapon& w) : Item(w), damage(w.damage),
	hands(w.hands) { }

uint32_t Weapon::get_hands() const {
    return hands;
 }

uint32_t Weapon::get_damage() const {
    return damage;
}

void Weapon::print(void) const {
	Item::print();
	std::cout << "Damage: " << damage << std::endl;
	std::cout << "Hands required: " << hands << std::endl;
}

