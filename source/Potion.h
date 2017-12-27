#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
	uint32_t restorationAmount;
    uint32_t potionType;
    bool availability;
public:
	Potion(std::string name, uint32_t pr, uint32_t min_level,
		uint32_t restoreAmount, uint32_t potType, bool avail) :
		Item(name, pr, min_level), restorationAmount(restoreAmount),
		potionType(potType), availability(avail) { }
	uint32_t get_Restoration_ammount() const {
		return restorationAmount;
	}
	uint32_t get_Potion_type() const {
		return potionType;
	}
	bool get_availability() const{
		return availability;
	}
	void set_availability(bool b){
		availability=b;
	}
};

#endif
