
#include <string>
#include "FireSpell.h"
#include "Spell.h"


FireSpell::FireSpell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t dmg[2], uint32_t m, uint32_t rAmount, uint32_t rnds) :
	Spell(nam, pr, min_level, type, dmg, m, rAmount, rnds)
{ }

std::string FireSpell::reduceStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
	armor -= reductionAmount;
	return "defense";
}

void FireSpell::restoreStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) {
	armor += reductionAmount;
}

void FireSpell::print(void) const {
	Spell::print();
	std::cout << "Spell Type: Fire Spell" << std::endl;
}
