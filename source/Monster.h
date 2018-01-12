#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <cstdint>
#include "Living.h"

typedef uint8_t monsterType;
namespace monsterTypes { 
	const uint8_t Dragon = 0;
	const uint8_t Exoskeleton = 1;
	const uint8_t Spirit = 2;
	const char *const monsterNames[] = { "Dragon", "Exoskeleton", "Spirit" };
};

struct monsterInfo_t {
	uint32_t damage[2];
	uint32_t armor;
	uint32_t agility;
};

class Monster : public Living {
private:
	struct monsterInfo_t monsterInfo;
	const struct monsterInfo_t *const initialData;
	monsterType type;
public:
	Monster(const struct livingInfo_t& li, const struct monsterInfo_t *const mi, monsterType t) :
	     Living(li), initialData(mi), type(t) {
			 monsterInfo.damage[0] = mi->damage[0];
			 monsterInfo.damage[1] = mi->damage[1];
			 monsterInfo.armor = mi->armor;
			 monsterInfo.agility = mi->agility;
		 }

	void receiveAttack(uint32_t opDamage) {
		if(monsterInfo.armor > opDamage) {
			monsterInfo.armor -= opDamage;
		} else {
			uint32_t temp = (opDamage - monsterInfo.armor);
			if(livingInfo.healthPower > temp)
				livingInfo.healthPower -= temp;
			else {
				livingInfo.healthPower = 0;
				livingInfo.awake = false;
			}
			monsterInfo.armor = 0;
		}
	}

	monsterType getMonsterType(void) const {
		return type;
	}

	void setDamageRange(uint32_t low, uint32_t high) {
		monsterInfo.damage[0] = low;
		monsterInfo.damage[1] = high;
	}

	void setArmor(uint32_t armor) {
		monsterInfo.armor = armor;
	}

	void setAgility(uint32_t agility) {
		monsterInfo.agility = agility;
	}

	uint32_t getAttackDamage() const {
		uint32_t res = rand() % (monsterInfo.damage[1] - monsterInfo.damage[0]) + monsterInfo.damage[0];
		return res;
	}

	bool willGetAttacked(void) const {
		uint32_t x = rand() % 101;
		if(x < monsterInfo.agility)
			return false;
		return true;
	}

	void regenerate(uint32_t healthToRegen) {
		if(livingInfo.healthPower + healthToRegen < livingInfo.initialHealthPower)
			livingInfo.healthPower += healthToRegen;
	}


	void printInfo(void) const {
		std::cout << "Type: " << monsterTypes::monsterNames[type] << std::endl;
		std::cout << "Name: " << Living::getName() << std::endl;
		std::cout << "Level: "   << livingInfo.level << std::endl;
		std::cout << "Health: "   << livingInfo.healthPower << std::endl;
		std::cout << "Strength Low: "   << monsterInfo.damage[0] << std::endl;
		std::cout << "Strength High: "   << monsterInfo.damage[1] << std::endl;
		std::cout << "Armor: "  << monsterInfo.armor << std::endl;
		std::cout << "Agility: "    << monsterInfo.agility << std::endl;
	}
};

#endif
