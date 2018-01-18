#ifndef PALADIN_H
#define PALADIN_H

#include "Hero.h"

class Paladin : public Hero {
public:
	Paladin(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
		Hero(li, hi) { }

	bool tryLevelUp(void) {
		if(Hero::tryLevelUp()) {
			heroInfo.strength+=2;
			heroInfo.agility+=2;
			heroInfo.agility++;
			heroInfo.magicPower+=50;

			return true;
		}
		return false;
	}

	void printInfo(void) const {
		std::cout << "Type: " << "Paladin" << std::endl;
		Hero::printInfo();
	}
};

#endif
