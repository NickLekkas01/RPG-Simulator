#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

typedef uint32_t itemType;
namespace itemTypes {
	const uint32_t Weapon = 0;
	const uint32_t Spell = 1;
	const uint32_t Potion = 2;
	const uint32_t Armor = 3;
};

class Item {
private:
	std::string name;
	uint32_t price;
	uint32_t minimum_level;
	itemType iType;
public:
	Item(std::string, uint32_t, uint32_t, itemType) ;

	Item(const class Item&);
	
	std::string get_name() const;
	int get_price() const;

	itemType getItemType(void) const;

	uint8_t getMinLevel() const;

	virtual void print(void) const ;
};

#endif
