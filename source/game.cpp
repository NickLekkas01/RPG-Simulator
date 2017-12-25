#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stdint.h>
#include "Hero.h"
#include "Monster.h"
#include "Weapon.h"
#include "Spell.h"
#include "utils.h"

#define INPUT_FILE_ERROR 1

using namespace std;

namespace playerChoices {
	int32_t initializeHeroes = 2;
	enum { quit, printMap, moveHeroes, checkInventory};
	const char* choices[] = {"Quit: 0", "Print Map: 1", "Initialize Heroes: 2",
	"Move Heroes: 3", "Check Inventory: 4"};
};

int main(void) {
	bool Running = true;
	struct defaultData_t defaultData;
	if(!defaultData.readDefaultData())
		return INPUT_FILE_ERROR;

	cout << defaultData.initialHealthPower << endl;
	cout << defaultData.exoskeletonInfo.armor << endl;
	
	class Map map;
	if(!map.readMap())
		return INPUT_FILE_ERROR;
	cout << "Welcome to the RPG game" << endl;

	// Initial loop
	while(Running) {
		int32_t choice;
		cout << "Available choices" << endl;
		cout << "Quit: 0" << endl;
		cout << "Print Map: 1" << endl;
		cout << "Initialize heroes Positions: 2" << endl;
		cout << "What do you want to do? ";
		cin >> choice;
		if(choice == playerChoices::quit) {
			Running = false;
		} else if(choice == playerChoices::printMap) {
			map.print();
		} else if(choice == playerChoices::initializeHeroes) {
			while(true) {
				int32_t position[2];
				cout << "Where do you want to start? " << endl;
				cin >> position[0];
				cin >> position[1];
				if(map.initializeHeroesPosition(position))
					break;
				cout << "You can't start there!" << endl;
			}
			break;
		} else {
			cout << "This operation can't be handled!" << endl;
		}
	}

    //NOTE(nikos): we should add the choices of taking an potion, or equiping a weapon
    //NOTE(stefanos): Right! I just added the movement
	size_t storeSize = 20;
	class Item **store = new Item*[storeSize];
	// NOTE(stefanos): Manual initialization of items
	for(int i = 0; i < storeSize; ++i)
		store[i] = NULL;
	store[0] = new Weapon("Sword", 15, 3, 27, 1);
	uint32_t dmg[2] = {30, 50};
	store[1] = new Spell("Lighting", 25, 2, dmg, 17, IceSpell);
	for(int i = 0; i < storeSize; ++i) {
		if(store[i] != NULL)
			store[i]->print();
	}
	while(Running) {
		int32_t choice;
		cout << "Available choices" << endl;
		cout << "Quit: 0" << endl;
		cout << "Print Map: 1" << endl;
		cout << "Move Heroes: 2" << endl;
		cout << "What do you want to do? ";
		cin >> choice;
		if(choice == playerChoices::quit) {
			Running = false;
		} else if(choice == playerChoices::printMap) {
			map.print();
		} else if(choice == playerChoices::moveHeroes) {
			cout << "You can go:" << endl;
			cout << "Up: " << directions::up << endl;
			cout << "Down: " << directions::down << endl;
			cout << "Left: " << directions::left << endl;
			cout << "Right: " << directions::right << endl;
			cout << "Go Back: -1" << endl;
			cout << "Where do you want to go? " << endl;
			cin >> choice;
			if(choice == -1) { }
			if(!map.moveHeroes(choice)) {
				cout << "You can't go there!" << endl;
			}
		} else {
			cout << "This operation can't be handled!" << endl;
		}
	}
	
	delete[] store;
	return 0;
}
