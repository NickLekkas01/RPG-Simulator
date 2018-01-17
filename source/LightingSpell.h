#ifndef LIGHTINGSPELL_H
#define LIGHTINGSPELL_H

#include <string>
#include "Spell.h"

class LightingSpell : public Spell {
public:
	LightingSpell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t dmg[2], uint32_t m, uint32_t rAmount, uint32_t rnds) :
		Spell(nam, pr, min_level, type, dmg, m, rAmount, rnds)
	{ }

	std::string reduceStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
		agility -= reductionAmount;
		return "agility";
	}

	void restoreStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
		agility += reductionAmount;
	}

	void print(void) const {
		Spell::print();
		std::cout << "Spell Type: Lighting Spell" << std::endl;
	}
};

#endif
