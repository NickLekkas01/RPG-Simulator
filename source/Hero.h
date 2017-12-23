#ifndef HERO_H
#define HERO_H

#include <iostream>
#include "Living.h"

struct warriorInfo_t {
	uint32_t strength;
	uint32_t dexterity;
};

struct paladinInfo_t {
	uint32_t strength;
	uint32_t agility;
};

struct sorcererInfo_t {
	uint32_t dexterity;
	uint32_t agility;
};

typedef uint8_t heroType;
namespace heroTypes { 
	uint8_t Warrior = 0;
	uint8_t Sorcerer = 1;
	uint8_t Palladin = 2;
};

struct heroInfo_t {
	uint32_t magicPower;
	uint32_t strength;
	uint32_t dexterity;
	uint32_t agility;
	uint32_t money;
	uint32_t exp;
};

class Hero : public Living {
private:
	struct heroInfo_t heroInfo;
	heroType type;
public:
	Hero(const struct livingInfo& li, const struct heroInfo& hi, uint8_t t) :
	     Living(li), hInfo(hi), type(t) { }
	void printInfo(void) const {
		std::cout << "magicPower: " << heroInfo.magicPower << std::endl;
		std::cout << "Strength: "   << heroInfo.strength << std::endl;
		std::cout << "Dexterity: "  << heroInfo.dexterity << std::endl;
		std::cout << "Agility: "    << heroInfo.agility << std::endl;
		std::cout << "Money: "      << heroInfo.money << std::endl;
		std::cout << "Experience: " << heroInfo.exp << std::endl;
	}

	// NOTE(stefanos): Explain how the (exp > 100) and (exp = exp - 100)
	// logic works.
	void levelUp(){
		if(exp>100){
			Living::livingInfo.level++;
			if(/*type==Warrior*/){
				strength+=2;
				agility+=2;
				dexterity++;
				magicPower+=30;
				Living::livingInfo.healthPower+=100;
			}
			else if(/*type==Paladin*/){
				strength+=2;
				dexterity+=2;
				agility++;
				magicPower+=50;
				Living::livingInfo.healthPower+=80;
			}
			else if(/*type==Sorcerer*/){
				dexterity+=2;
				agility+=2;
				strenth+=1;
				magicPower+=100;
				Living::livingInfo.healthPower+=50;
			}
			money+=500;
			exp=exp-100;
		}
	}

};

#endif
