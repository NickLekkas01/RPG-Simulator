#ifndef SORCERER_H
#define SORCERER_H

#include <iostream>
#include "Hero.h"

class Sorcerer : public Hero {
public:
	Sorcerer(const struct livingInfo_t&, const struct heroInfo_t *const);

	bool tryLevelUp(void);

	void printInfo(void) const ;
};

#endif
