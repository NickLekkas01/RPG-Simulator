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
	Weapon(std::string, uint32_t, uint32_t, itemType,
		uint32_t, uint32_t) ;

	Weapon(const class Weapon&);

    uint32_t get_hands() const ;

    uint32_t get_damage() const ;

	void print(void) const ;
};

#endif
