#ifndef LIGHTINGSPELL_H
#define LIGHTINGSPELL_H

#include <string>
#include "Spell.h"

class LightingSpell : public Spell {
public:
	LightingSpell(std::string, uint32_t, uint32_t, itemType,
		uint32_t*, uint32_t, uint32_t, uint32_t);

	std::string reduceStats(uint32_t&, uint32_t&, uint32_t&);

	void restoreStats(uint32_t&, uint32_t&, uint32_t&);

	void print(void) const;
};

#endif
