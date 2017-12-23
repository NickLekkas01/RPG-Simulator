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
	     Living(li), heroInfo(hi), type(t) { }
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

	//ΝΟΤΕ(nikos): We'll have an the experience of each player, and by winning a monster he will gain experience. If his experience 
	// passes 100 then he grows one level and the remaining experience is for the next level.
	//Also i used comments in if's because i'm not so sure about how the variable type works ( just type==0  or type==1 or type==2 ?)
	void levelUp(){
		if(heroInfo.exp>100){
			Living::add_level(1);
			if(type==0){
				heroInfo.strength+=2;
				heroInfo.agility+=2;
				heroInfo.dexterity++;
				heroInfo.magicPower+=30;
				Living::set_health(100);
			}
			else if(type==1){
				heroInfo.strength+=2;
				heroInfo.dexterity+=2;
				heroInfo.agility++;
				heroInfo.magicPower+=50;
				Living::set_health(80);
			}
			else if(type==2){
				heroInfo.dexterity+=2;
				heroInfo.agility+=2;
				heroInfo.strength+=1;
				heroInfo.magicPower+=100;
				Living::set_health(50);
			}
			heroInfo.money+=500;
			heroInfo.exp=heroInfo.exp-100;
		}
	}

};

#endif
