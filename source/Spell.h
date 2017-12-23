#ifndef SPELL_H
#define SPELL_H

#include "Item.h"

enum spellType { IceSpell, FireSpell, LightingSpell };

class Spell : public Item {
private:
	uint32_t damage[2];
	uint32_t mana;
	uint8_t minimumLevel;
	enum spellType type;
};

#endif
