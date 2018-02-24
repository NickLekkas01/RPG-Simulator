//#ifndef ICESPELL_H
//#define ICESPELL_H

#include <string>
#include "Spell.h"

class IceSpell : public Spell {
public:
	IceSpell(std::string, uint32_t, uint32_t, itemType,
		uint32_t*, uint32_t, uint32_t, uint32_t) ;

	std::string reduceStats(uint32_t& , uint32_t& , uint32_t& );

	void restoreStats(uint32_t& , uint32_t& , uint32_t& );

	void print(void)const;
};

//#endif
