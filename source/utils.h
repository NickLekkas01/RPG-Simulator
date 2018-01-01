#ifndef UTILS_H
#define UTILS_H

#include <istream>
#include <cstdint>
#include "Hero.h"
#include "Item.h"
#include "Weapon.h"
#include "Spell.h"
#include "Potion.h"
#include "Monster.h"


// TODO(stefanos): Think if it is better to put
// in warrior, paladin and sorcerer all the info
// and eliminate the hero Info
struct defaultData_t {
public:
	uint32_t initialHealthPower;
	uint32_t probabilityToFight;  // at % percentage
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
	uint32_t numHeroes;
	class Hero **heroes;
	class Monster **monsters;

	int isValidPosition(int32_t*) const;
public:
	Map();
	~Map();
	int readMap(void);
	void print(void) const;
	void printHeroInfo(void) const {
		for(uint32_t i = 0; i < numHeroes; ++i) {
			if(heroes[i] != NULL)
				heroes[i]->printInfo();
			std::cout << std::endl;
		}
	}
	int initializeHeroesPosition(int32_t*);

	class Hero *searchHero(std::string name) {
		if(heroes != NULL) {
			for(uint32_t i = 0; i < numHeroes; ++i) {
				if(heroes[i] != NULL)
					if(heroes[i]->getName() == name) {
						return heroes[i];
					}
			}
		}

		return NULL;
	}
	void setNumHeroes(uint32_t num_heroes) {
		numHeroes = num_heroes;
		heroes = new Hero*[num_heroes];
		for(uint32_t i = 0; i < num_heroes; ++i)
			heroes[i] = NULL;
	}
	// TODO(stefanos): DEBUG CODE - REMOVE THAT
	/*
	void printHeroes(void) const {
		std::cout << "Printing heroes" << std::endl;
		if(heroes != NULL) {    // Assume that we have space
			for(uint32_t i = 0; i < numHeroes; ++i)
				if(heroes[i] != NULL) {
					heroes[i]->printInfo();
				}
		}

	}
	*/
	void createMonsters(void) {
		return;
	}

	void createHero(const struct livingInfo_t& livingInfo, 
		struct heroInfo_t& heroInfo, uint32_t heroClass) {

		// TODO(stefanos): Add more error checking
		if(heroes != NULL) {    // Assume that we have space
			for(uint32_t i = 0; i < numHeroes; ++i)
				if(heroes[i] == NULL) {
					heroes[i] = new Hero(livingInfo, heroInfo, heroClass);
					return;
				}
		}
	}
	int heroesInitialized(void) const { return (heroesPosition[0] != -1); }
	int moveHeroes(int32_t);

	int heroesOnStore(void) const {
		return (Grid[heroesPosition[0]][heroesPosition[1]] == 'S');
	}
};

struct itemLock {
	class Item* item;
	int taken;
};

class Store {
private:
	const size_t size;
	size_t currently_holding;
	class itemLock *items;
public:
	Store(size_t s) : size(s), currently_holding(0) {

		// Allocate the initial shared memory
		items = new itemLock[size];
		for(int i = 0; i < size; ++i) {
			items[i].item = NULL;
			items[i].taken = 0;
		}
	}
	
	int readItems(const std::string&);

	int hasAvailableSpace(void) const {
		return currently_holding < size;
	}

	class Item* searchItem(std::string name) {
		for(int i = 0; i < size; ++i)
			if(items[i].item != NULL && items[i].taken == 0) {
				if(items[i].item->get_name() == name) {
					return items[i].item;
				}
			}

		return NULL;

	}

	// Mark an item as taken
	class Item* removeItem(const std::string& name) {
		for(int i = 0; i < size; ++i)
			if(items[i].item->get_name() == name) {
				items[i].taken = 1;
				--currently_holding;
				return items[i].item;
			}
		return NULL;
	}

	// removes and deletes an item from memory
	int deleteItem(class Item *it) {
		if(it != NULL) {
			for(int i = 0; i < size; ++i)
				if(items[i].item == it) {
					delete items[i].item;
					items[i].item = NULL;
					items[i].taken = 0;
					--currently_holding;
					return 1;
				}
		}

		return 0;
	}

	// TODO(stefanos): Maybe add a return value for checking.
	void addItem(class Item *it) {

		// NOTE(stefanos): Put it in the initial
		// position (the position it was when you got it)
		for(int i = 0; i < size; ++i)
			if(items[i].item != NULL && items[i].item == it && items[i].taken == 1) {
				items[i].taken = 0;
				++currently_holding;
			}
	}
	
	// Print items using virtual functionality
	void print(void) const {
		std::cout << std::endl;
		std::cout << "Store Items" << std::endl;
		for(int i = 0; i < size; ++i) {
			if(items[i].item != NULL && items[i].taken == 0) {
				items[i].item->print();
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
	
	// Deallocate the initial memory
	~Store() {
		if(items != NULL) {
			for(int i = 0; i < size; ++i)
				if(items[i].item != NULL) {
					delete items[i].item;
				}
			delete[] items;
		}
	}
};

void skipComments(std::istream&);

#endif
