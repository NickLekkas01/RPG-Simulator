#ifndef PALADIN_H
#define PALADIN_H

#include <iostream>
#include "Hero.h"

class Paladin : public Hero {
public:
	Paladin(const struct livingInfo_t&, const struct heroInfo_t *const);

	bool tryLevelUp(void);

	void printInfo(void) const ;
};

#endif
