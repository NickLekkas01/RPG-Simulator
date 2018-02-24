#ifndef SPELL_H
#define SPELL_H

#include <string>
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
	uint32_t rounds;

protected:
	uint32_t reductionAmount;

public:
	Spell(std::string, uint32_t, uint32_t, itemType,
		uint32_t*, uint32_t, uint32_t, uint32_t);

	// NOTE(stefanos): Changes the respective stat depending on the kind of spell,
	// returns the name of the stat
	virtual std::string 
	reduceStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) = 0;
	
	virtual void
	restoreStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) = 0;

	uint32_t getReductionAmount(void) const ;

	uint32_t getRounds(void) const ;

	uint32_t getMinDamage();

	uint32_t getMaxDamage();

	uint32_t getMana();

	virtual void print(void) const ;
};

#endif
