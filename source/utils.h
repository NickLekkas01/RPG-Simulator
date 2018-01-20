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
	void freeMonsters(){
		for(uint32_t i = 0; i < numHeroes; ++i){
			if(monsters[i] != NULL){
				delete monsters[i];
				monsters[i] = NULL;
			}
		}
	}
	int readMap(void);
	void print(void) const;
	void printHeroInfo(void) const {
		for(uint32_t i = 0; i < numHeroes; ++i) {
			if(heroes[i] != NULL)
				heroes[i]->printInfo();
			std::cout << std::endl;
		}
	}

	uint32_t getNumHeroes(void) const {
		return numHeroes;
	}

	int initializeHeroesPosition(int32_t*);
	

	class Hero *searchHero(std::string name) const {
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

	class Hero *searchHero(uint32_t i) const {
		// Assume that we have allocated memory for 'heroes'
		return heroes[i];
	}

	class Monster *searchMonster(uint32_t i) const {
		// Assume that we have allocated memory for 'monsters'
		return monsters[i];
	}

	void generateMonsters(uint32_t healthPower) {
		// Assume that we have memory for monsters
		for(size_t i = 0; i < this->numHeroes; ++i) {
			class Hero *h = searchHero(i);
			uint32_t level = h->getLevel();
			std::stringstream name;
			name << "Monster " << i;
			struct livingInfo_t tempLivingInfo = {name.str(), level, healthPower, healthPower, 1};
			struct monsterInfo_t tempMonsterInfo;
			uint32_t heroStrength = h->getStrength();
			tempMonsterInfo.damage[0] = heroStrength - 20;
			tempMonsterInfo.damage[1] = rand() % ( (heroStrength + 10) - (heroStrength - 10) ) + (heroStrength - 10);
			tempMonsterInfo.armor = (level < 5) ? (level * 10) : (level * 0.4f);
			uint32_t heroAgility = h->getAgility();
			tempMonsterInfo.agility = rand() % ( (heroAgility  + 10) - (heroAgility - 10) ) + (heroAgility - 10);
			uint32_t type = rand() % 3;
			// TODO(stefanos): Make stats different for each monster
			/*
			if(type == monsterTypes::Dragon) {
			} else if(type == monsterTypes::Exoskeleton) {
			} else {    // Spirit
			}
			*/
			monsters[i] = new Monster(tempLivingInfo, tempMonsterInfo);
		}
	}

	void roundEnd(uint32_t healthToRegen, uint32_t magicPowerToRegen) {
		for(size_t i = 0; i < numHeroes; ++i) {
			class Hero *h = heroes[i];
			if(h->isAwake()) {
				h->regenerate(healthToRegen, magicPowerToRegen);
			}

			class Monster *m = monsters[i];
			if(m->isAwake()) {
				m->regenerate(healthToRegen);
			}
		}
	}

	bool allHeroesDead(void) const {
		for(size_t i = 0; i < numHeroes; ++i) {
			if(heroes[i]->isAwake())
				return false;
		}
		
		return true;
	}

	bool allMonstersDead(void) const {
		for(size_t i = 0; i < numHeroes; ++i) {
			if(monsters[i]->isAwake())
				return false;
		}
		
		return true;
	}

	bool fightEnded(void) const {
		if(allHeroesDead()) {
			std::cout << std::endl << std::endl;
			std::cout << "MONSTERS WON" << std::endl;
			std::cout << std::endl << std::endl;

			for(size_t i = 0; i < numHeroes; ++i) {
				heroes[i]->resetHealthToHalf();
				heroes[i]->setAwake(true);
				heroes[i]->resetMoneyToHalf();
			}

			return true;
		} else if(allMonstersDead()) {
			std::cout << std::endl << std::endl;
			std::cout << "HEROES WON" << std::endl;
			std::cout << std::endl << std::endl;

			for(size_t i = 0; i < numHeroes; ++i) {
				if(!heroes[i]->isAwake()) {
					heroes[i]->resetHealthToHalf();
					heroes[i]->setAwake(true);
				} else
					heroes[i]->resetHealth();
				
				heroes[i]->addExp(numHeroes * 10 + (heroes[i]->getLevel() / 100.0f));
				if(heroes[i]->tryLevelUp()) {
					std::cout << heroes[i]->getName() << " leveled up!" << std::endl;
				}
				heroes[i]->addMoney(500 + 500 * (heroes[i]->getLevel() / 100.0f));
			}

			return true;
		}

		return false;
	}

	void setNumHeroesAndMonsters(uint32_t num_heroes) {
		numHeroes = num_heroes;
		heroes = new Hero*[num_heroes];
		monsters = new Monster*[num_heroes];
		for(uint32_t i = 0; i < num_heroes; ++i) {
			heroes[i] = NULL;
			monsters[i] = NULL;
		}
	}

	void createHero(const struct livingInfo_t& livingInfo, 
		const struct heroInfo_t *const heroInfo, uint8_t heroClass) {

		if(heroes != NULL) {    // Assume that we have space
			for(uint32_t i = 0; i < numHeroes; ++i)
				if(heroes[i] == NULL) {
					if(heroClass == heroTypes::Warrior)
						heroes[i] = new Warrior(livingInfo, heroInfo);
					else if(heroClass == heroTypes::Paladin)
						heroes[i] = new Paladin(livingInfo, heroInfo);
					else
						heroes[i] = new Sorcerer(livingInfo, heroInfo);
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
	size_t size;
	size_t currently_holding;
	class itemLock *items;
public:
	Store() : currently_holding(0), size(0), items(NULL) { }

	Store(size_t s) : size(s), currently_holding(0) {

		// Allocate the initial shared memory
		items = new itemLock[size];
		for(int i = 0; i < size; ++i) {
			items[i].item = NULL;
			items[i].taken = 0;
		}
	}
	
	int readItems(const std::string&);

	bool hasAvailableSpace(void) const {
		return (currently_holding < size);
	}

	class Item* searchItem(const std::string& name) {
		for(int i = 0; i < size; ++i)
			if(items[i].item != NULL && items[i].taken == 0) {
				if(items[i].item->get_name() == name) {
					return items[i].item;
				}
			}

		return NULL;

	}

	// Mark an item as taken
	bool removeItem(class Item *it) {
		for(int i = 0; i < size; ++i) {
			if(items[i].item == it) {
				items[i].taken = 1;
				--currently_holding;
				return true;
			}
		}
		return false;
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
