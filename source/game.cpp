#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stdint.h>
#include "Hero.h"
#include "Monster.h"
#include "utils.h"

#define INPUT_FILE_ERROR 1

class Map {
public:
	uint32_t Height;
	uint32_t Width;
	uint8_t **Grid;

	int readMap(void);
};

using namespace std;

int Map::readMap(void) {
	// Read the map
	ifstream mapFile("./build/map.dat");
	if(!mapFile.good()) {
		cout << "There was a problem opening the data input" << endl;
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
}

int main(void) {
	
	// File location relative to the COMPILER
	// TODO(stefanos): Remove that from the release
	ifstream dataFile("./build/defaultData.dat");
	if(!dataFile.good()) {
		cout << "There was a problem opening the data input" << endl;
		return INPUT_FILE_ERROR;
	}

	struct defaultData_t defaultData;
	readDefaultData(dataFile, defaultData);

	cout << defaultData.initialHealthPower << endl;
	cout << defaultData.exoskeletonInfo.armor << endl;

	dataFile.close();
	
	class Map map;
	if(!map.readMap())
		return INPUT_FILE_ERROR;
	for(int y = 0; y < map.Height; ++y) {
		for(int x = 0; x < map.Width; ++x) {
			cout << map.Grid[y][x];
		}
		cout << endl;
	}

	// Cleanup
	for(int y = 0; y < map.Height; ++y) {
		delete[] map.Grid[y];
	}
	delete[] map.Grid;

	return 0;
}
