#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <cstdint>
#include "Living.h"


struct dragonInfo_t {
	uint32_t damage[2];
};

struct exoskeletonInfo_t {
	uint32_t armor;
};

struct spiritInfo_t {
	uint32_t agility;
};

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
	monsterType type;
public:
	Monster(const struct livingInfo_t& li, const struct monsterInfo_t& mi, monsterType t) :
	     Living(li), monsterInfo(mi), type(t) { }

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


	// NOTE(stefanos):
	// Generate accesses private data of Hero, which is wrong. Better with
	// getters but more importantly,
 	// possibly we only care for the level of the monster,
	// so we don't have to pass a hero to Generate(), just
	// the level of the monster we want to generate and have
	// some kind of dynamic generation (i.e. agility = 1.5 * level).
	// In that way, we remove the dependency with Hero.
	// Also, Generate() should be the constructor, because it is
	// in the gameplay side (that's me :D )when we generate a monster
	// and we construct it based on the level and some default data.
	// Lastly, explain how agility works in terms of what it affects and
	// how because I have no idea of those games. :P

	// NOTE(nikos) I agree with the part of not giving the whole class, but shouldn't the prices
	// of agility,armor and health be equal of the ones of the hero? We can give the level and the other prices.
	//another thought is: Will we generate a monster for each hero based on his statistics?
	// And by that I mean having a 11 level monster,15 level monster if we have an 11 level hero and an 15 level hero
	//About how agility effects the damage, im not sure but we could rise the value of minimum damage if we see high agility(something like that)
	void Generate(uint8_t lev, uint32_t health, uint32_t agil){
			Living::add_level(lev);
            Living::set_health(health);
			if(type==0){
                Living::set_name("Dragon");
				monsterInfo.damage[0]=10;
                monsterInfo.damage[1]=50;
                monsterInfo.armor=5;
                monsterInfo.agility=agil;
			}
			else if(type==1){
                Living::set_name("Exoskeleton");
				monsterInfo.damage[0]=10;
                monsterInfo.damage[1]=30;
                monsterInfo.armor=10;
                monsterInfo.agility=agil;
			}
			else if(type==2){
                Living::set_name("Spirit");
				monsterInfo.damage[0]=10;
                monsterInfo.damage[1]=30;
                monsterInfo.armor=3;
                monsterInfo.agility=agil+5;
			}
		}
};

#endif
