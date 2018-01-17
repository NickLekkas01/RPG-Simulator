#ifndef ICESPELL_H
#define ICESPELL_H

#include <string>
#include "Spell.h"

class IceSpell : public Spell {
public:
	IceSpell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
		uint32_t dmg[2], uint32_t m, uint32_t rAmount, uint32_t rnds) :
		Spell(nam, pr, min_level, type, dmg, m, rAmount, rnds)
	{ }

	std::string reduceStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
		highDamage -= reductionAmount;
		return "damage range";
	}

	void restoreStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
		highDamage += reductionAmount;
	}


	void print(void) const {
		Spell::print();
		std::cout << "Spell Type: Ice Spell" << std::endl;
	}
};

#endif
