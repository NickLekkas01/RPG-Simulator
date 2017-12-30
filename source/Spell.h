#ifndef SPELL_H
#define SPELL_H

#include "Item.h"

enum spellType { IceSpell, FireSpell, LightingSpell };

class Spell : public Item {
private:
	uint32_t damage[2];
	uint32_t mana;
	// NOTE(stefanos): minimum level is part of Item
	// which we inherit
	// uint8_t minimumLevel;
	enum spellType type;
	const uint32_t hands;
public:
	Spell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t dmg[2], uint32_t m, enum spellType t) :
		Item(nam, pr, min_level, type), mana(m), type(t), hands(1) {
		damage[0] = dmg[0];
		damage[1] = dmg[1];
	}

	uint32_t get_hands(void) const { return hands; }

	void print(void) const {
		Item::print();
		std::cout << "Damage Low: " << damage[0] << std::endl;
		std::cout << "Damage High: " << damage[1] << std::endl;
		// TODO(stefanos): For now only the integer. Implement
		// naming for spell types
		std::cout << "Spell Type: " << type << std::endl;
	}
};

#endif
