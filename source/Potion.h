#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
	uint32_t Restoration_ammount;
    uint32_t Potion_type;
    bool availability;
public:
	uint32_t get_Restoration_ammount() const {
		return Restoration_ammount;
	}
	uint32_t get_Potion_type() const {
		return Potion_type;
	}
	bool get_availability() const{
		return availability;
	}
	void set_availability(bool b){
		availability=b;
	}
};

#endif