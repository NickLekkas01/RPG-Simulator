#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include "Hero.h"

class Warrior : public Hero {
public:
	Warrior(const struct livingInfo_t&, const struct heroInfo_t *const);

	bool tryLevelUp(void) ;

	void printInfo(void) const ;
};

#endif
