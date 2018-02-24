
#include <iostream>
#include "Sorcerer.h"
#include "Hero.h"


Sorcerer::Sorcerer(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
	Hero(li, hi) { }

bool Sorcerer::tryLevelUp(void) {
	if(Hero::tryLevelUp()) {
		heroInfo.strength+=2;
		heroInfo.agility+=2;
		++heroInfo.strength;
		heroInfo.magicPower+=100;

		return true;
	}
	return false;
}

void Sorcerer::printInfo(void) const {
	std::cout << "Type: Sorcerer" << std::endl;
	Hero::printInfo();
}


