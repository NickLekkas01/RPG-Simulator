#ifndef WEAPON_H
#define WEPON_H

#include "Item.h"

class Weapon : public Item {
private:
	uint32_t damage;
	int8_t hands;      // 0 -> 1 hand, 1 -> both
};

#endif
