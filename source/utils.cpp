#include <string>
#include <iostream>
#include <cstdint>
#include <istream>
#include <fstream>
#include <csignal>
#include "HealthPotion.h"
#include "StrengthPotion.h"
#include "DexterityPotion.h"
#include "AgilityPotion.h"
#include "utils.h"
#include "IceSpell.h"
#include "FireSpell.h"
#include "LightingSpell.h"

void assert_null_function(void) {}
#define assert(condition) \
 if (!(condition)) { \
   fprintf(stderr, "%s:%d: `%s' assert failed\n", \
       __FILE__, __LINE__, #condition); \
   raise(SIGKILL); \
 } \
 assert_null_function()


// (stefanos): Any line starting with a #
// is a comment
void skipComments(std::istream& dataFile) {
	char c;

	while(!dataFile.eof()) {
		c = dataFile.get();
		int32_t temp = c;
		if(c == '#') {
			while((c = dataFile.get()) != '\n' && c != '\r')
			{ }
			return;
		} else if(c == '\n' || c == '\r') {
			continue;
		} else {
			dataFile.unget();
			return;
		}
	}
}

// (stefanos): Read default data for hero types and monster types.
int defaultData_t::readDefaultData() {
	std::ifstream dataFile("./build/defaultData.dat");
	if(!dataFile.good()) {
		std::cout << "There was a problem opening the data dataFile" << std::endl;
		return 0;
	}

	skipComments(dataFile);
	dataFile >> initialHealthPower;
	
	std::string dataClass;
	skipComments(dataFile);
	while(dataFile >> dataClass) {
		if(dataClass == "Warrior") {
			dataFile >> warriorInfo.magicPower;
			dataFile >> warriorInfo.money;
			dataFile >> warriorInfo.exp;
			dataFile >> warriorInfo.strength;
			dataFile >> warriorInfo.dexterity;
			dataFile >> warriorInfo.agility;
		} else if(dataClass == "Paladin") {
			dataFile >> paladinInfo.magicPower;
			dataFile >> paladinInfo.money;
			dataFile >> paladinInfo.exp;
			dataFile >> paladinInfo.strength;
			dataFile >> paladinInfo.dexterity;
			dataFile >> paladinInfo.agility;
		} else if(dataClass == "Sorcerer") {
			dataFile >> sorcererInfo.magicPower;
			dataFile >> sorcererInfo.money;
			dataFile >> sorcererInfo.exp;
			dataFile >> sorcererInfo.strength;
			dataFile >> sorcererInfo.dexterity;
			dataFile >> sorcererInfo.agility;
		}
	}

	dataFile.close();
	
	return 1;
}


/// MAP IMPLEMENTATION ///
Map::Map() : Height(0), Width(0), Grid(NULL), heroes(NULL), monsters(NULL) {
	heroesPosition[0] = -1;
	heroesPosition[1] = -1;
}

Map::~Map() {
	// Cleanup
	uint32_t height = Height;
	uint8_t **grid = Grid;
	for(int y = 0; y < height; ++y) {
		if(grid[y] != NULL) {
			delete[] grid[y];
		}
	}
	delete[] grid;
	Grid = NULL;
	
	if(heroes != NULL) {
		for(uint32_t i = 0; i < numHeroes; ++i)
			if(heroes[i] != NULL)
				delete heroes[i];
		delete[] heroes;
		heroes = NULL;
	}

	if(monsters != NULL) {
		for(uint32_t i = 0; i < numHeroes; ++i)
			if(monsters[i] != NULL)
				delete monsters[i];
		delete[] monsters;
		monsters = NULL;
	}
}

int Map::readMap(void) {
	// Read the map
	std::ifstream mapFile("./build/map.dat");
	if(!mapFile.good()) {
		std::cout << "There was a problem opening the data input" << std::endl;
		return 0;
	}
		
	// Use local variables to avoid cache misses
	uint32_t width, height;
	mapFile >> height;
	mapFile >> width;
	Height = height;
	Width = width;
	uint8_t **grid = new uint8_t*[height];
	for(int y = 0; y < height; ++y) {
		grid[y] = new uint8_t[width];
	}
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			mapFile >> grid[y][x];
		}
	}

	
	Grid = grid;
	mapFile.close();

	return 1;
}

void Map::print(void) const {
	uint8_t **grid = Grid;
	uint32_t height = Height;
	uint32_t width = Width;
	uint8_t padding = 4;
	for(int y = 0; y < height; ++y) {
		int x;
		std::cout << std::endl;
		for(int x = 0; x < width; ++x) {
			for(int i = 0; i < padding; ++i)
				std::cout << " ";
			if(grid[y][x] == 'S' && heroesPosition[0] == y && heroesPosition[1] == x)
				std::cout << "HS";
			else
				std::cout << grid[y][x] << " ";
		}
		for(int i = 0; i < padding/2 - 1; ++i) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

int Map::isValidPosition(int32_t position[2]) const {
	if(!(position[0] >= 0 && position[1] >= 0))
		return 0;
	if(!(position[0] < Height && position[1] < Width))
		return 0;
	char square = Grid[position[0]][position[1]];
	if(square == 'N')
		return 0;

	return 1;
}

int Map::initializeHeroesPosition(int32_t position[2]) {
	if(isValidPosition(position)) {
		heroesPosition[0] = position[0];
		heroesPosition[1] = position[1];
		if(Grid[position[0]][position[1]] != 'S')
			Grid[position[0]][position[1]] = 'H';
		return 1;
	}
	return 0;
}

void Map::freeMonsters(){
		for(uint32_t i = 0; i < numHeroes; ++i){
			if(monsters[i] != NULL){
				delete monsters[i];
				monsters[i] = NULL;
			}
		}
	}

void Map::printHeroInfo(void) const {
		for(uint32_t i = 0; i < numHeroes; ++i) {
			if(heroes[i] != NULL)
				heroes[i]->printInfo();
			std::cout << std::endl;
		}
	}

class Hero *Map::searchHero(std::string name) const {
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

	class Hero *Map::searchHero(uint32_t i) const {
		// Assume that we have allocated memory for 'heroes'
		return heroes[i];
	}

	class Monster *Map::searchMonster(uint32_t i) const {
		// Assume that we have allocated memory for 'monsters'
		return monsters[i];
	}

	void Map::generateMonsters(uint32_t healthPower) {
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
			
			if(type == 0) {							//monsterTypes::Dragon
				tempMonsterInfo.damage[0] *= 1.3;
				tempMonsterInfo.damage[1] *= 1.3;
			} else if(type == 1) {					//monsterTypes::Exoskeleton
				tempMonsterInfo.armor *= 1.3;
			} else {    							//monsterTypes::Spirit
				tempMonsterInfo.agility *= 1.3;
			}
			
			monsters[i] = new Monster(tempLivingInfo, tempMonsterInfo);
		}
	}

	void Map::roundEnd(uint32_t healthToRegen, uint32_t magicPowerToRegen) {
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

	bool Map::allHeroesDead(void) const {
		for(size_t i = 0; i < numHeroes; ++i) {
			if(heroes[i]->isAwake())
				return false;
		}
		
		return true;
	}

	bool Map::allMonstersDead(void) const {
		for(size_t i = 0; i < numHeroes; ++i) {
			if(monsters[i]->isAwake())
				return false;
		}
		
		return true;
	}

	bool Map::fightEnded(void) const {
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

	void Map::setNumHeroesAndMonsters(uint32_t num_heroes) {
		numHeroes = num_heroes;
		heroes = new Hero*[num_heroes];
		monsters = new Monster*[num_heroes];
		for(uint32_t i = 0; i < num_heroes; ++i) {
			heroes[i] = NULL;
			monsters[i] = NULL;
		}
	}

	void Map::createHero(const struct livingInfo_t& livingInfo, 
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

	uint32_t Map::getNumHeroes(void) const {
		return numHeroes;
	}

	int Map::heroesInitialized(void) const { return (heroesPosition[0] != -1); }

	int Map::heroesOnStore(void) const {
		return (Grid[heroesPosition[0]][heroesPosition[1]] == 'S');
	}

int Map::moveHeroes(int32_t direction) {
	// IMPORTANT!
	// NOTE(stefanos): You can only move to common squares
	// If you want to interact with the store, you have to go in front of the
	// store.
	int32_t position[2] = { heroesPosition[0], heroesPosition[1] };
	if(direction == directions::up) {
		position[0] -= 1;
	} else if(direction == directions::down) {
		position[0] += 1;
	} else if(direction == directions::left) {
		position[1] -= 1;
	} else if(direction == directions::right) {
		position[1] += 1;
	}
	if(!isValidPosition(position))
		return 0;
	
	// reveert back only if they were in a common square
	if(Grid[heroesPosition[0]][heroesPosition[1]] != 'S')
		Grid[heroesPosition[0]][heroesPosition[1]] = 'C';
	heroesPosition[0] = position[0];
	heroesPosition[1] = position[1];

	// Change the content of this square only
	// if it is a common square
	if(Grid[position[0]][position[1]] != 'S')
		Grid[position[0]][position[1]] = 'H';

	return 1;
}

Store::Store() : currently_holding(0), size(0), items(NULL) { }

Store::Store(size_t s) : size(s), currently_holding(0) {

		// Allocate the initial shared memory
		items = new itemLock[size];
		for(int i = 0; i < size; ++i) {
			items[i].item = NULL;
			items[i].taken = 0;
		}
	}

	bool Store::hasAvailableSpace(void) const {
		return (currently_holding < size);
	}

class Item* Store::searchItem(const std::string& name) {
		for(int i = 0; i < size; ++i)
			if(items[i].item != NULL && items[i].taken == 0) {
				if(items[i].item->get_name() == name) {
					return items[i].item;
				}
			}

		return NULL;

	}

	// Mark an item as taken
	bool Store::removeItem(class Item *it) {
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
	int Store::deleteItem(class Item *it) {
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
	void Store::addItem(class Item *it) {

		// NOTE(stefanos): Put it in the initial
		// position (the position it was when you got it)
		for(int i = 0; i < size; ++i)
			if(items[i].item != NULL && items[i].item == it && items[i].taken == 1) {
				items[i].taken = 0;
				++currently_holding;
			}
	}

	// Print items using virtual functionality
	void Store::print(void) const {
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
	Store::~Store() {
		if(items != NULL) {
			for(int i = 0; i < size; ++i)
				if(items[i].item != NULL) {
					delete items[i].item;
				}
			delete[] items;
		}
	}

int Store::readItems(const std::string& fileName) {
	std::cout << std::endl << "GREETING" << std::endl;
	std::ifstream itemsFile(fileName);
	if(!itemsFile.good()) {
		std::cout << "There was a problem opening the items data file" << std::endl;
		return 0;
	}

	skipComments(itemsFile);

	// Read the number of items
	size_t storeSize;
	itemsFile >> storeSize;
	this->size = storeSize;

	// Allocate the initial shared memory
	items = new itemLock[storeSize];
	for(int i = 0; i < storeSize; ++i) {
		items[i].item = NULL;
		items[i].taken = 0;
	}

	skipComments(itemsFile);
	std::string itemClass;
	size_t itemsRead = 0;
	while(itemsFile >> itemClass && itemsRead < storeSize) {
		std::string name;
		uint32_t price, min_level;
		size_t i = itemsRead;

		if(itemClass == "Weapon") {
			uint32_t damage, hands;
			itemsFile >> name >> price >> min_level >> damage >> hands;
			items[i].item = new Weapon(name, price, min_level, 
				itemTypes::Weapon, damage, hands);
		} else if(itemClass == "Spell") {
			uint32_t damage[2], mana, reductionAmount, rounds;
			std::string spell_type;
			itemsFile >> name >> price >> min_level >> damage[0] >> damage[1] 
				>> mana >> reductionAmount >> rounds >> spell_type;
			if(spell_type == "IceSpell") {
				items[i].item = new IceSpell(name, price, min_level,
					itemTypes::Spell, damage, mana, reductionAmount, rounds);
			} else if(spell_type == "FireSpell") {
				items[i].item = new FireSpell(name, price, min_level,
					itemTypes::Spell, damage, mana, reductionAmount, rounds);
			} else {
				items[i].item = new LightingSpell(name, price, min_level,
					itemTypes::Spell, damage, mana, reductionAmount, rounds);
			}

		} else if(itemClass == "Potion") {
			uint32_t restoration_amount;
			std::string potion_type;
			
			itemsFile >> name >> price >> min_level >> restoration_amount >> potion_type;
			if(potion_type == "Health") {
				items[i].item = new HealthPotion(name, price, min_level, 
					itemTypes::Potion, restoration_amount);
			} else if(potion_type == "Strength") {
				items[i].item = new StrengthPotion(name, price, min_level, 
					itemTypes::Potion, restoration_amount);
			} else if(potion_type == "Dexterity") {
				items[i].item = new DexterityPotion(name, price, min_level, 
					itemTypes::Potion, restoration_amount);
			} else {
				items[i].item = new AgilityPotion(name, price, min_level, 
					itemTypes::Potion, restoration_amount);
			}
		} else if(itemClass == "Armor") {
			uint32_t armorValue;

			itemsFile >> name >> price >> min_level >> armorValue;
			items[i].item = new Armor(name, price, min_level, itemTypes::Armor, armorValue);
		}

		items[i].taken = 0;

		skipComments(itemsFile);

		++itemsRead;
	}

	this->currently_holding = itemsRead;

	itemsFile.close();
	
	return 1;

}
