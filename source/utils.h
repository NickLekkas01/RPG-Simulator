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

	void readItems(void) {

		// Read items
		// TODO(stefanos): Those items are to be read from a file
		items[0].item = new Weapon("Sword", 15, 3, 40, 1);
		currently_holding++;
		uint32_t damage[2] = {30, 50};
		items[1].item = new Spell("MySpell", 12, 2, damage, 34, IceSpell);
		currently_holding++;
	}

	int hasAvailableSpace(void) const {
		return currently_holding < size;
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
	
	// Print items using virtual functionality
	void print(void) const {
		for(int i = 0; i < size; ++i) {
			if(items[i].item != NULL && items[i].taken == 0)
				items[i].item->print();
		}
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
