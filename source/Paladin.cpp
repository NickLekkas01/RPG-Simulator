
#include <iostream>
#include "Paladin.h"
#include "Hero.h"


	Paladin::Paladin(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
		Hero(li, hi) { }

	bool Paladin::tryLevelUp(void) {
		if(Hero::tryLevelUp()) {
			heroInfo.strength+=2;
			heroInfo.dexterity+=2;
			heroInfo.agility++;
			heroInfo.magicPower+=20;

			return true;
		}
		return false;
	}

	void Paladin::printInfo(void) const {
		std::cout << "Type: Paladin" << std::endl;
		Hero::printInfo();
	}

