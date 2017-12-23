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
};

#endif
