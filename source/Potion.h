#ifndef POTION_H
#define POTION_H

#include "Item.h"

typedef uint32_t potionType;
namespace potionTypes{
	enum { health, strength, dexterity, agility };
	//const char* potionNames[] = 
}

class Potion : public Item {
private:
	uint32_t restorationAmount;
    potionType type;
    bool availability;
public:
	Potion(std::string name, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t restoreAmount, potionType potType, bool avail) :
		Item(name, pr, min_level, type), restorationAmount(restoreAmount),
		type(potType), availability(avail) { }
	uint32_t get_Restoration_ammount() const {
		return restorationAmount;
	}
	uint32_t get_Potion_type() const {
		return type;
	}
	bool get_availability() const{
		return availability;
	}
	void set_availability(bool b){
		availability=b;
	}

	void print(void) const {
		Item::print();
		std::cout << "Restoration Amount: " << restorationAmount << std::endl;
		std::cout << "Availability: " << availability << std::endl;
		// TODO(stefanos): For now only the integer. Implement
		// naming for spell types
		std::cout << "Spell Type: " << type << std::endl;
	}

};

#endif
