
#include <iostream>
#include "Warrior.h"
#include "Hero.h"


Warrior::Warrior(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
	Hero(li, hi) { }

bool Warrior::tryLevelUp(void) {
	if(Hero::tryLevelUp()) {
		heroInfo.strength+=2;
		heroInfo.agility+=2;
		heroInfo.dexterity++;
		heroInfo.magicPower+=30;

		return true;
	}
	return false;
}

void Warrior::printInfo(void) const {
	std::cout << "Type: Warrior" << std::endl;
	Hero::printInfo();
}

