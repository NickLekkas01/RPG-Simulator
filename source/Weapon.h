#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <cstdint>
#include "Item.h"

class Weapon : public Item {
private:
	uint32_t damage;
	uint32_t hands;      // 1 -> 1 hand, 2 -> both
public:
	Weapon(std::string nam, uint32_t pr, uint32_t min_level,
		uint32_t dmg, uint32_t h) :
		Item(nam, pr, min_level), damage(dmg), hands(h) { }

	Weapon(const class Weapon& w) : Item(w), damage(w.damage),
		hands(w.hands) { }
	
	void print(void) const {
		Item::print();
		std::cout << "Damage: " << damage << std::endl;
		std::cout << "Hands required: " << hands << std::endl;
	}
};

#endif
