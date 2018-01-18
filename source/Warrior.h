#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include "Hero.h"

class Warrior : public Hero {
public:
	Warrior(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
		Hero(li, hi) { }

	bool tryLevelUp(void) {
		if(Hero::tryLevelUp()) {
			heroInfo.strength+=2;
			heroInfo.agility+=2;
			heroInfo.dexterity++;
			heroInfo.magicPower+=30;

			return true;
		}
		return false;
	}

	void printInfo(void) const {
		std::cout << "Type: Warrior" << std::endl;
		Hero::printInfo();
	}
};

#endif
