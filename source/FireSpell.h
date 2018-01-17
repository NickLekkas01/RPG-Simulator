#ifndef FIRESPELL_H
#define FIRESPELL_H

#include <string>
#include "Spell.h"

class FireSpell : public Spell {
public:
	FireSpell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t dmg[2], uint32_t m, uint32_t rAmount, uint32_t rnds) :
		Spell(nam, pr, min_level, type, dmg, m, rAmount, rnds)
	{ }

	std::string reduceStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
		armor -= reductionAmount;
		return "defense";
	}

	void restoreStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
		armor += reductionAmount;
	}

	void print(void) const {
		Spell::print();
		std::cout << "Spell Type: Fire Spell" << std::endl;
	}
};

#endif
