#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
	uint32_t Restoration_ammount;
    uint32_t Potion_type;
    bool availability;
};

#endif