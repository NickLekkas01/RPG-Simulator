#ifndef HERO_H
#define HERO_H

#include <iostream>
#include "Living.h"

// struct defaultWarrior {		
// 	uint32_t strength;
// 	uint32_t dexterity;
// };

typedef uint8_t heroType;
namespace heroTypes { 
	const uint8_t Warrior = 0;
	const uint8_t Sorcerer = 1;
	const uint8_t Palladin = 2;
};

struct heroInfo {
	uint32_t magicPower;
	uint32_t strength;
	uint32_t dexterity;
	uint32_t agility;
	uint32_t money;
	uint32_t exp;
};

class Hero : public Living {
private:
	struct heroInfo hInfo;
	heroType type;
public:
	Hero(const struct livingInfo& li, const struct heroInfo& hi, uint8_t t) :
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
	void levelUp(){
		if(exp>100){
			Living::lInfo.level++;
			if(/*type==Warrior*/){
				strength+=2;
				agility+=2;
				dexterity++;
				magicPower+=30;
				Living::lInfo.healthPower+=100;
			}
			else if(/*type==Paladin*/){
				strength+=2;
				dexterity+=2;
				agility++;
				magicPower+=50;
				Living::lInfo.healthPower+=80;
			}
			else if(/*type==Sorcerer*/){
				dexterity+=2;
				agility+=2;
				strenth+=1;
				magicPower+=100;
				Living::lInfo.healthPower+=50;
			}
			money+=500;
			exp=exp-100;
		}
	}
};

#endif
