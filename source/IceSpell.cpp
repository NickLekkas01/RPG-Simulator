#ifndef ICESPELL_H
#define ICESPELL_H

#include <string>
#include "IceSpell.h"
#include "Spell.h"



IceSpell::IceSpell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t dmg[2], uint32_t m, uint32_t rAmount, uint32_t rnds) :
	Spell(nam, pr, min_level, type, dmg, m, rAmount, rnds)
{ }

std::string IceSpell::reduceStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
	highDamage -= reductionAmount;
	return "damage range";
}

void IceSpell::restoreStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
	highDamage += reductionAmount;
}


void IceSpell::print(void) const {
	Spell::print();
	std::cout << "Spell Type: Ice Spell" << std::endl;
}


#endif
