
#include <iostream>
#include <cstdint>
#include "Monster.h"
#include "Living.h"

Monster::Monster(const struct livingInfo_t& li, const struct monsterInfo_t& mi) : Living(li)
{

		// TODO(stefanos): Test with initializer list

		std::cout << "Damage: " << mi.damage[0] << std::endl;
		std::cout << "Armor: " << mi.armor << std::endl;
		std::cout << "Agility: " << mi.agility << std::endl;
		monsterInfo.damage[0] = mi.damage[0];
		monsterInfo.damage[1] = mi.damage[1];
		monsterInfo.armor = mi.armor;
		monsterInfo.agility = mi.agility;
	 }

void Monster::receiveAttack(uint32_t opDamage) {
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

uint32_t Monster::getStats(uint32_t& highDamage, uint32_t& armor, uint32_t& agility) const {
	highDamage = monsterInfo.damage[1];
	armor = monsterInfo.armor;
	agility = monsterInfo.agility;
}

void Monster::setStats(uint32_t highDamage, uint32_t armor, uint32_t agility) {
	monsterInfo.damage[1] = highDamage;
	monsterInfo.armor = armor;
	monsterInfo.agility = agility;
}

uint32_t Monster::getAttackDamage() const {
	uint32_t res = rand() % (monsterInfo.damage[1] - monsterInfo.damage[0]) + monsterInfo.damage[0];
	return res;
}

bool Monster::willGetAttacked(void) const {
	uint32_t x = rand() % 101;
	if(x < monsterInfo.agility)
		return false;
	return true;
}

void Monster::regenerate(uint32_t healthToRegen) {
	if(livingInfo.healthPower + healthToRegen < livingInfo.initialHealthPower)
		livingInfo.healthPower += healthToRegen;
}


void Monster::printInfo(void) const {
	std::cout << "Name: " << Living::getName() << std::endl;
	std::cout << "Level: "   << livingInfo.level << std::endl;
	std::cout << "Health: "   << livingInfo.healthPower << std::endl;
	std::cout << "Strength Low: "   << monsterInfo.damage[0] << std::endl;
	std::cout << "Strength High: "   << monsterInfo.damage[1] << std::endl;
	std::cout << "Armor: "  << monsterInfo.armor << std::endl;
	std::cout << "Agility: "    << monsterInfo.agility << std::endl;
}

