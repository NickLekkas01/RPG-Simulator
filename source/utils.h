#ifndef UTILS_H
#define UTILS_H

#include <istream>
#include <cstdint>
#include <string>
#include <sstream>
#include "Hero.h"
#include "Warrior.h"
#include "Paladin.h"
#include "Sorcerer.h"
#include "Item.h"
#include "Weapon.h"
#include "Spell.h"
#include "Potion.h"
#include "Armor.h"
#include "Monster.h"

struct defaultData_t {
public:
	uint32_t initialHealthPower;
	uint32_t healthToRegen;
	uint32_t magicPowerToRegen;
	
	// Heroes
	struct heroInfo_t warriorInfo;
	struct heroInfo_t paladinInfo;
	struct heroInfo_t sorcererInfo;
	
	// Monster
	struct monsterInfo_t dragonInfo;
	struct monsterInfo_t exoskeletonInfo;
	struct monsterInfo_t spiritInfo;


	defaultData_t() { }
	~defaultData_t() { }
	int readDefaultData(void);
};

namespace heroTypes {
	const uint8_t Warrior = 0;
	const uint8_t Paladin = 1;
	const uint8_t Sorcerer = 2;
};

enum directions { up, down, right, left };
class Map {
private:
	uint32_t Height;
	uint32_t Width;
	uint8_t **Grid;
	int32_t heroesPosition[2];
	uint32_t numHeroes;
	class Hero **heroes;
	class Monster **monsters;

	int isValidPosition(int32_t*) const;
public:
	Map();
	~Map();
	void freeMonsters();
	int readMap(void);
	void print(void) const;
	void printHeroInfo(void) const ;

	uint32_t getNumHeroes(void) const ;

	int initializeHeroesPosition(int32_t*);
	

	class Hero *searchHero(std::string ) const ;

	class Hero *searchHero(uint32_t) const ;

	class Monster *searchMonster(uint32_t) const ;

	void generateMonsters(uint32_t ) ;

	void roundEnd(uint32_t, uint32_t) ;

	bool allHeroesDead(void) const ;

	bool allMonstersDead(void) const ;

	bool fightEnded(void) const ;

	void setNumHeroesAndMonsters(uint32_t) ;

	void createHero(const struct livingInfo_t&, 
		const struct heroInfo_t *const, uint8_t) ;
		
	int heroesInitialized(void) const ;

	int moveHeroes(int32_t);

	int heroesOnStore(void) const ;
};

struct itemLock {
	class Item* item;
	int taken;
};

class Store {
private:
	size_t size;
	size_t currently_holding;
	class itemLock *items;
public:
	Store() ;

	Store(size_t) ;
	
	int readItems(const std::string&);

	bool hasAvailableSpace(void) const ;

	class Item* searchItem(const std::string&) ;

	// Mark an item as taken
	bool removeItem(class Item *) ;

	// removes and deletes an item from memory
	int deleteItem(class Item *) ;

	// TODO(stefanos): Maybe add a return value for checking.
	void addItem(class Item *) ;
	
	// Print items using virtual functionality
	void print(void) const ;
	
	// Deallocate the initial memory
	~Store() ;
};

void skipComments(std::istream&);

#endif
