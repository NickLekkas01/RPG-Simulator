#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include "Living.h"


struct dragonInfo_t {
	uint32_t strength;
	uint32_t dexterity;
};

struct exoskeletonInfo_t {
	uint32_t strength;
	uint32_t agility;
};

struct spiritInfo_t {
	uint32_t dexterity;
	uint32_t agility;
};

typedef uint8_t monsterType;
namespace monsterTypes { 
	const uint8_t Dragon = 0;
	const uint8_t Exoskeleton = 1;
	const uint8_t Spirit = 2;
};

struct monsterInfo_t {
	uint32_t damage[2];
	uint32_t armor;
	uint32_t agility;

	// NOTE(stefanos): In the monster, we only care about the level
	// because it spawns for just one round (i.e. the experience has
	// no meaning in the game)
	uint32_t exp;
};

class Monster : public Living {
private:
	struct monsterInfo_t monsterInfo;
	monsterType type;
public:
	Monster(const struct livingInfo_t& li, const struct monsterInfo_t& mi, monsterType t) :
	     Living(li), monsterInfo(mi), type(t) { }
	/*
	void printInfo(void) const {
		std::cout << "Type: " << type << std::endl;
		std::cout << "magicPower: " << hInfo.magicPower << std::endl;
		std::cout << "Strength: "   << hInfo.strength << std::endl;
		std::cout << "Dexterity: "  << hInfo.dexterity << std::endl;
		std::cout << "Agility: "    << hInfo.agility << std::endl;
		std::cout << "Money: "      << hInfo.money << std::endl;
		std::cout << "Experience: " << hInfo.exp << std::endl;
	}
	*/
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
