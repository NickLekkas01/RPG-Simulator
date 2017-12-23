#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include "Living.h"

// struct defaultWarrior {		
// 	uint32_t strength;
// 	uint32_t dexterity;
// };

typedef uint8_t monsterType;
namespace monsterTypes { 
	const uint8_t Dragon = 0;
	const uint8_t Exoskeleton = 1;
	const uint8_t Spirit = 2;
};

struct monsterInfo {
	uint32_t damage[2];
	uint32_t armor;
	uint32_t agility;
	uint32_t exp;
};

class Monster : public Living {
private:
	struct monsterInfo mInfo;
	monsterType type;
public:
	Monster(const struct livingInfo& li, const struct monsterInfo& hi, uint8_t t) :
	     Living(li), hInfo(hi), type(t) { }
	void printInfo(void) const {
		std::cout << "Type: " << type << std::endl;
		std::cout << "magicPower: " << hInfo.magicPower << std::endl;
		std::cout << "Strength: "   << hInfo.strength << std::endl;
		std::cout << "Dexterity: "  << hInfo.dexterity << std::endl;
		std::cout << "Agility: "    << hInfo.agility << std::endl;
		std::cout << "Money: "      << hInfo.money << std::endl;
		std::cout << "Experience: " << hInfo.exp << std::endl;
	}
	void Generate(class Hero H){
			Living::level=H.Living::level;
            Living::healthPower=H.Living::healthPower+50;
            exp=0;
			if(/*type==Dragon*/){
                Living::name="Dragon";
				damage[0]=10;
                damage[1]=50;
                armor=5;
                agility=H.hInfo.agility;
			}
			else if(/*type==Exoskeleton*/){
                Living::name="Exoskeleton";
				damage[0]=10;
                damage[1]=30;
                armor=10;
                agility=H.hInfo.agility;
			}
			else if(/*type==Spirit*/){
                Living::name="Spirit";
				damage[0]=10;
                damage[1]=30;
                armor=3;
                agility=H.hInfo.agility+5;
			}
		}
};

#endif
