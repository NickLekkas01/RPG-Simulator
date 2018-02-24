#ifndef FIRESPELL_H
#define FIRESPELL_H

#include <string>
#include "Spell.h"

class FireSpell : public Spell {
public:
	FireSpell(std::string, uint32_t, uint32_t, itemType,
		uint32_t*, uint32_t, uint32_t, uint32_t);

	std::string reduceStats(uint32_t&, uint32_t&, uint32_t&);

	void restoreStats(uint32_t& highDamage, uint32_t&, uint32_t&);

	void print(void) const;
};

#endif
