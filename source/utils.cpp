#include <string>
#include <iostream>
#include <cstdint>
#include <istream>
#include <fstream>
#include <csignal>
#include "utils.h"

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
	std::string s;

	while(!dataFile.eof()) {
		c = dataFile.get();
		if(c == '#') {
			getline(dataFile, s);
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
		if(dataClass == "Hero") {
			dataFile >> heroInfo.magicPower;
			dataFile >> heroInfo.strength;
			dataFile >> heroInfo.dexterity;
			dataFile >> heroInfo.agility;
			dataFile >> heroInfo.money;
			dataFile >> heroInfo.exp;
		} else if(dataClass == "Warrior") {
			dataFile >> warriorInfo.strength;
			dataFile >> warriorInfo.dexterity;
		} else if(dataClass == "Paladin") {
			dataFile >> paladinInfo.strength;
			dataFile >> paladinInfo.agility;
		} else if(dataClass == "Sorcerer") {
			dataFile >> sorcererInfo.dexterity;
			dataFile >> sorcererInfo.agility;
		}
		if(dataClass == "Monster") {
			dataFile >> monsterInfo.damage[0];
			dataFile >> monsterInfo.damage[1];
			dataFile >> monsterInfo.armor;
			dataFile >> monsterInfo.agility;
		} else if(dataClass == "Dragon") {
			dataFile >> dragonInfo.damage[0];
			dataFile >> dragonInfo.damage[1];
		} else if(dataClass == "Exoskeleton") {
			dataFile >> exoskeletonInfo.armor;
		} else if(dataClass == "Spirit") {
			dataFile >> spiritInfo.agility;
		}
	}

	dataFile.close();
	
	return 1;
}


/// MAP IMPLEMENTATION ///
Map::Map() : Height(0), Width(0), Grid(NULL) {
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

void Map::print(void) {
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
			std::cout << grid[y][x] << " ";
		}
		for(int i = 0; i < padding/2 - 1; ++i) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

int Map::initializeHeroesPosition(int32_t position[2]) {
	assert(position[0] >= 0 && position[1] >= 0);
	assert(position[0] < Height && position[1] < Width);
	char square = Grid[position[0]][position[1]];
	if(square == 'N' || square == 'I')
		return 0;
	Grid[position[0]][position[1]] = 'H';
	return 1;
}
