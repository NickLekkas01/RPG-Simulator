#ifndef SPELL_H
#define SPELL_H

#include "Item.h"

typedef uint8_t spellType;
namespace spellTypes {
	const uint8_t IceSpell = 0;
	const uint8_t FireSpell = 1;
	const uint8_t LightingSpell = 2;
	const char *const typeNames[] = { "Ice Spell", "Fire Spell", "Lighting Spell" };
};

class Spell : public Item {
private:
	uint32_t damage[2];
	uint32_t mana;
	uint32_t reductionAmount;
	spellType type;
public:
	Spell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t dmg[2], uint32_t m, uint32_t rAmount, spellType t) :
		Item(nam, pr, min_level, type), reductionAmount(rAmount), mana(m), type(t) {
		damage[0] = dmg[0];
		damage[1] = dmg[1];
	}

	spellType getSpellType(void) const {
		return type;
	}

	uint32_t getReductionAmount(void) const {
		return reductionAmount;
	}

	uint32_t getMinDamage(){
		return damage[0];
	}

	uint32_t getMaxDamage(){
		return damage[1];
	}

	uint32_t getMana(){
		return mana;
	}

	void print(void) const {
		Item::print();
		std::cout << "Spell Type: " << spellTypes::typeNames[type] << std::endl;
		std::cout << "Damage Low: " << damage[0] << std::endl;
		std::cout << "Damage High: " << damage[1] << std::endl;
		std::cout << "Reduction Amount: " << reductionAmount << std::endl;
		std::cout << "Mana: " << mana << std::endl;
	}
};

#endif
