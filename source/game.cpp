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
	enum { quit, printMap, moveHeroes, checkInventory, usePotion, checkStoreItems, buy, sell};
};

int main(void) {
	bool Running = true;
	struct defaultData_t defaultData;
	if(!defaultData.readDefaultData())
		return INPUT_FILE_ERROR;

	cout << defaultData.initialHealthPower << endl;
	cout << defaultData.exoskeletonInfo.armor << endl;
	
	class Map map(3);
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
	//NOTE(nikos): relax boi

	

	// Initialize the store
	// NOTE(stefanos): Shared memory for the store. Items getting to the inventory
	// have the memory from the store. Memory gets destroyed when we don't need
	// the store anymore. Provided that any item that any hero has is taken
	// from the store, this is the end of the game.

	// TODO(stefanos): Multiple stores?
	class Store store(10);
	// TODO(stefanos): Path relative to the compiler
	// Fix that on the release
	store.readItems("./build/items.dat");

	// TODO(stefanos): Put a default living info data to defaultData_t
	struct livingInfo_t livingInfo {"Stefanos", 7, defaultData.initialHealthPower, defaultData.initialHealthPower, 1};
	// NOTE(stefanos): Test code for one hero
	class Hero h(livingInfo, defaultData.heroInfo, heroTypes::Warrior);
	while(Running) {
		int32_t choice;
		cout << "Available choices" << endl;
		cout << "Quit: 0" << endl;
		cout << "Print Map: 1" << endl;
		cout << "Move Heroes: 2" << endl;
		cout << "Check inventory: 3" << endl;
		cout << "Use Potion: 4" << endl;
		if(map.heroesOnStore()) {
			cout << "Check items avaialble on the store: 5" << endl;
			cout << "Buy something: 6" << endl;
			cout << "Sell something: 7" << endl;
		}
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
		// TODO(stefanos): Think about the fact that a player
		// can actually commit store choices even though
		// they do not see them.
		} else if(choice == playerChoices::checkInventory) {
				h.checkInventory();
		} else if(choice == playerChoices::usePotion) {
			h.printPotions();
		} else if(map.heroesOnStore()) {
			if(choice == playerChoices::checkStoreItems) {
				store.print();

			// NOTE(stefanos): Assume that everything we do is for one hero,
			// TODO: Fix that!
			} else if(choice == playerChoices::buy) {
				if(!h.inventoryAvaiableSpace()) {
					cout << "Not enough space on the inventory" << endl;
					continue;
				}
				string name;
				store.print();
				cout << "Type the name of the item you want to buy: ";
				cin >> name;
				class Item *it = store.searchItem(name);
				if(it == NULL) {
					cout << "That item is not on the store" << endl;
					continue;
				}
				if(!h.hasEnoughMoney(it)) {
					cout << "You don't have enough money to buy this item" << endl;
					continue;
				}
				// TODO(stefanos): Take into consideration the return value??
				h.buy(store.removeItem(name));
			} else if(choice == playerChoices::sell) {
				// NOTE(stefanos): The procedure is the same with the buy,
				// just for the store now. Notice, that all the items that
				// players have, come from the store. So, it's impossible
				// for the store to not have space, so we don't check that.

				// Show the items that they already have
				h.checkInventory();
				string name;
				cout << "Type the name of the item you want to sell: ";
				cin >> name;
				store.addItem(h.sell(name));
			}
		} else {
			cout << "This operation can't be handled!" << endl;
		}
	}
	
	return 0;
}
