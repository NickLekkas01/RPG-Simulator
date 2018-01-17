#include <string>
#include <iostream>
#include <cstdint>
#include <istream>
#include <fstream>
#include <csignal>
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
		std::cout << "INT: " << temp << std::endl;
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

		if(dataClass == "Dragon") {
			dataFile >> dragonInfo.damage[0];
			dataFile >> dragonInfo.damage[1];
			dataFile >> dragonInfo.armor;
			dataFile >> dragonInfo.agility;
		} else if(dataClass == "Exoskeleton") {
			dataFile >> exoskeletonInfo.damage[0];
			dataFile >> exoskeletonInfo.damage[1];
			dataFile >> exoskeletonInfo.armor;
			dataFile >> exoskeletonInfo.agility;
		} else if(dataClass == "Spirit") {
			dataFile >> spiritInfo.damage[0];
			dataFile >> spiritInfo.damage[1];
			dataFile >> spiritInfo.armor;
			dataFile >> spiritInfo.agility;
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

int Store::readItems(const std::string& fileName) {
	std::cout << "GREETING" << std::endl;
	std::ifstream itemsFile(fileName);
	if(!itemsFile.good()) {
		std::cout << "There was a problem opening the items data file" << std::endl;
		return 0;
	}

	skipComments(itemsFile);

	// Read the number of items
	size_t storeSize;
	itemsFile >> storeSize;
	std::cout << "ANOTHER: " << storeSize << std::endl;
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

		skipComments(itemsFile);
		std::cout << "ItemsClass: " << itemClass << std::endl;
		if(itemClass == "Weapon") {
			std::cout << "WEAPON" << std::endl;
			uint32_t damage, hands;
			itemsFile >> name >> price >> min_level >> damage >> hands;
			items[i].item = new Weapon(name, price, min_level, 
				itemTypes::Weapon, damage, hands);
			items[i].taken = 0;

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

			items[i].taken = 0;
		} else if(itemClass == "Potion") {
			uint32_t restoration_amount;
			uint32_t potion_type;

			itemsFile >> name >> price >> min_level >> restoration_amount >> potion_type;
			items[i].item = new Potion(name, price, min_level, 
				itemTypes::Potion, restoration_amount,
				potion_type);
		} else if(itemClass == "Armor") {
			uint32_t armorValue;

			itemsFile >> name >> price >> min_level >> armorValue;
			items[i].item = new Armor(name, price, min_level, itemTypes::Armor, armorValue);
			items[i].taken = 0;
		}

		std::cout << "HERE: " << name << std::endl;

		++itemsRead;
	}

	this->currently_holding = itemsRead;

	itemsFile.close();
	
	return 1;

}
