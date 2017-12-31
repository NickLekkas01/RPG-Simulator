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
	enum { quit, printMap, moveHeroes, checkInventory, heroInfo, usePotion, equip, unequip, checkStoreItems, buy, sell};
};

void handleHeroSpecificChoices(int32_t choice, class Hero *h, class Store& store, class Map& map) {

	if(choice == playerChoices::checkInventory) {
		h->checkInventory();
	} else if(choice == playerChoices::heroInfo) {
		h->printInfo();
	} else if(choice == playerChoices::usePotion) {
		h->printPotions();
		cout << "Type the name of the potion: " << endl;
		string name;
		cin >> name;
		class Item *it = h->usePotion(name);
		if(it == NULL) {
			cout << "The potion either does not exist, or you are " \
				"not in the required level to use it" << endl;
			return;
		}
		if(h->getLevel() < it->get_minimumLevel()) {
			cout << "You are not on the required level to use this potion" << endl;
			return;
		} else {
			store.deleteItem(it);
		}
	} else if(choice == playerChoices::equip) {
		if(h->isInventoryEmpty()) {
			cout << "There is nothing to equip" << endl;
			return;
		}
		h->printWeapons();
		cout << "Type the name of the weapon you want to equip: " << endl;
		string name;
		cin >> name;
		class Item *it = h->searchItem(name);
		if(it == NULL) {
			cout << "The weapon does not exist" << endl;
			return;
		} else if(it->getItemType() != itemTypes::Weapon) {
			cout << "You can only equip weapons" << endl;
			return;
		} else if(!h->isOnRequiredLevel(it)) {
	        cout << "You are not on the required level to equip the weapon" << endl;
	        return;
	    } else if(h->isInUse(it)) {
	        cout << "The item is already equipped" << endl;
	        return;
	    }
		if(!h->equipWeapon(it)) {
	        cout << "Could not equip the weapon because there are other weapons in use." << endl;
	    }
	} else if(choice == playerChoices::unequip){
	    h->checkInventory();
	    cout << "Type the name of the weapon you want to unequip: " << endl;
	    string name;
	    cin >> name;
	    class Item *it = h->searchItem(name);
	    if(it == NULL) {
	        cout << "The weapon does not exist" << endl;
	        return;
	    } else if(!h->isInUse(it)) {
	        cout << "The weapon is not equipped" << endl;
	        return;
	    }
	    h->unequipWeapon(it);
	} else if(map.heroesOnStore()) {
		if(choice == playerChoices::checkStoreItems) {
			store.print();

		} else if(choice == playerChoices::buy) {
			if(!h->inventoryAvaiableSpace()) {
				cout << "Not enough space on the inventory" << endl;
				return;
			}
			string name;
			store.print();
			cout << "Type the name of the item you want to buy: ";
			cin >> name;
			class Item *it = store.searchItem(name);
			if(it == NULL) {
				cout << "That item is not on the store" << endl;
				return;
			}
			if(!h->hasEnoughMoney(it)) {
				cout << "You don't have enough money to buy this item" << endl;
				return;
			}
			h->buy(store.removeItem(name));
		} else if(choice == playerChoices::sell) {
	        // NOTE(stefanos): The procedure is the same with the buy,
	        // just for the store now. Notice, that all the items that
	        // players have, come from the store. So, it's impossible
	        // for the store to not have space, so we don't check that.

	        // Show the items that they already have
	        h->checkInventory();
	        string name;
	        cout << "Type the name of the item you want to sell: ";
	        cin >> name;
	        class Item *it = h->searchItem(name);
	        if (it == NULL) {
	            cout << "This item is not on the inventory" << endl;
	        } else if(h->isInUse(it)) {
	            cout << "This item is in use. Unequip it first if you want to sell it." << endl;
	        } else {
				store.addItem(h->sell(name));
			}
		}
	}
}

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

	// TODO(stefanos): Gets seg faul here
	while(!Running) {
		return 0;
	}

	// Initialize the store
	// NOTE(stefanos): Shared memory for the store. Items getting to the inventory
	// have the memory from the store. Memory gets destroyed when we don't need
	// the store anymore. Provided that any item that any hero has is taken
	// from the store, this is the end of the game.

	class Store store(10);
	// TODO(stefanos): Path relative to the compiler
	// Fix that on the release
	store.readItems("./build/items.dat");

	uint32_t num_heroes;
	do {
		cout << "How many heroes do you want (1-3)? " << endl;
		cin >> num_heroes;
	} while(num_heroes < 1 || num_heroes > 3);
	map.setNumHeroes(num_heroes);
	for(int i = 0; i < num_heroes; ++i) {
		struct livingInfo_t livingInfo = {"", 7, defaultData.initialHealthPower, defaultData.initialHealthPower, 1};
		cout << "Type the name of the hero " << i + 1 << ": ";
		cin >> livingInfo.name;

		string heroClass;
		cout << "Type the class you want this hero to have: ";
		cin >> heroClass;
		map.createHero(livingInfo, defaultData.heroInfo, heroClass); 
	}

	/* TODO(stefanos): DEBUG CODE - REMOVE THAT
	map.printHeroes();
	*/
	while(Running) {
		int32_t choice;
		cout << "Available choices" << endl;
		cout << "Quit: 0" << endl;
		cout << "Print Map: 1" << endl;
		cout << "Move Heroes: 2" << endl;
		cout << "Check inventory: 3" << endl;
		cout << "Display Hero Info: 4" << endl;
		cout << "Use Potion: 5" << endl;
		cout << "Equip Weapon: 6" << endl;
		cout << "Unequip Weapon: 7" << endl;
		if(map.heroesOnStore()) {
			cout << "Check items avaialble on the store: 8" << endl;
			cout << "Buy something: 9" << endl;
			cout << "Sell something: 10" << endl;
		}
		cout << "What do you want to do? ";
		cin >> choice;

		if(choice > 10) {
			cout << "This operation can't be handled" << endl;
			continue;
		}
		if(choice == playerChoices::quit) {
			Running = false;
		} else if(choice == playerChoices::printMap) {
			map.print();
		} else if(choice == playerChoices::moveHeroes) {
			cout << "You can go:" << endl;
			cout << "Up: " << directions::up << endl;
			cout << "Down: " << directions::down << endl;
			cout << "Right: " << directions::right << endl;
			cout << "Left: " << directions::left << endl;
			cout << "Go Back: -1" << endl;
			cout << "Where do you want to go? " << endl;
			cin >> choice;
			if(choice == -1) { }
			if(!map.moveHeroes(choice)) {
				cout << "You can't go there!" << endl;
			}
		} else {
			string name;
			cout << "Type the name of the hero you want " \
				"to do this operation for: " << endl;
			cin >> name;
			class Hero *h = map.searchHero(name);
			if(h == NULL) {
				cout << "Sorry, that hero does not exist" << endl;
				continue;
			}

			handleHeroSpecificChoices(choice, h, store, map);
		}
	}
	
	return 0;
}
