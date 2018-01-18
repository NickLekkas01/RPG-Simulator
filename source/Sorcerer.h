#ifndef SORCERER_H
#define SORCERER_H

#include "Hero.h"

class Sorcerer : public Hero {
public:
	Sorcerer(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
		Hero(li, hi) { }

	bool tryLevelUp(void) {
		if(Hero::tryLevelUp()) {
			heroInfo.strength+=2;
			heroInfo.agility+=2;
			++heroInfo.strength;
			heroInfo.magicPower+=100;

			return true;
		}
		return false;
	}

	void printInfo(void) const {
		std::cout << "Type: " << "Sorcerer" << std::endl;
		Hero::printInfo();
	}
};

#endif
