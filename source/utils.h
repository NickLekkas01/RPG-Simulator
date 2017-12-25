#ifndef UTILS_H
#define UTILS_H

#include <istream>
#include <cstdint>
#include "Hero.h"
#include "Monster.h"


// TODO(stefanos): Think if it is better to put
// in warrior, paladin and sorcerer all the info
// and eliminate the hero Info
struct defaultData_t {
public:
	uint32_t initialHealthPower;
	// Hero
	struct heroInfo_t heroInfo;
	struct warriorInfo_t warriorInfo;
	struct paladinInfo_t paladinInfo;
	struct sorcererInfo_t sorcererInfo;
	
	// Monster
	struct monsterInfo_t monsterInfo;
	struct dragonInfo_t dragonInfo;
	struct exoskeletonInfo_t exoskeletonInfo;
	struct spiritInfo_t spiritInfo;


	defaultData_t() { }
	~defaultData_t() { }
	int readDefaultData(void);
};


enum directions { up, down, right, left };
class Map {
private:
	uint32_t Height;
	uint32_t Width;
	uint8_t **Grid;
	int32_t heroesPosition[2];

	int isValidPosition(int32_t*) const;
public:
	Map();
	~Map();
	int readMap(void);
	void print(void) const;
	int initializeHeroesPosition(int32_t*);
	int heroesInitialized(void) const { return (heroesPosition[0] != -1); }
	int moveHeroes(int32_t);
};

void skipComments(std::istream&);
void readDefaultData(std::istream&, struct defaultData_t&);

#endif
