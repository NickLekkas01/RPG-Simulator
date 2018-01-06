#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include "Hero.h"
#include "Monster.h"
#include "Weapon.h"
#include "Spell.h"
#include "utils.h"

#define INPUT_FILE_ERROR 1

using namespace std;

namespace playerChoices {
	int32_t initializeHeroes = 2;
	enum { quit, printMap, moveHeroes, checkInventory, heroInfo, usePotion, equipWeapon, unequipWeapon, equipArmor, unequipArmor, checkStoreItems, buy, sell};
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
		if(h->getLevel() < it->getMinLevel()) {
			cout << "You are not on the required level to use this potion" << endl;
			return;
		} else {
			store.deleteItem(it);
		}
	} else if(choice == playerChoices::equipWeapon) {
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
	} else if(choice == playerChoices::unequipWeapon) {
		h->checkInventory();
		cout << "Type the name of the weapon you want to unequip: " << endl;
		string name;
		cin >> name;
		class Item *it = h->searchItem(name);
		if (it == NULL) {
			cout << "The weapon does not exist" << endl;
			return;
		} else if (!h->isInUse(it)) {
			cout << "The weapon is not equipped" << endl;
			return;
		}
		h->unequipWeapon(it);
	} else if(choice == playerChoices::equipArmor) {
		if(h->isInventoryEmpty()) {
			cout << "There is nothing to equip" << endl;
			return;
		}
		h->printArmors();
		cout << "Type the name of the armor you want to equip: " << endl;
		string name;
		cin >> name;
		class Item *it = h->searchItem(name);
		if(it == NULL) {
			cout << "The armor does not exist" << endl;
			return;
		} else if(it->getItemType() != itemTypes::Armor) {
			cout << "You can only equip armors" << endl;
			return;
		} else if(!h->isOnRequiredLevel(it)) {
			cout << "You are not on the required level to equip the armor" << endl;
			return;
		} else if(h->isInUse(it)) {
			cout << "The armor is already equipped" << endl;
			return;
		}
		if(!h->equipArmor(it)) {
			cout << "Could not equip the armor because there are other armors in use." << endl;
		}
	} else if(choice == playerChoices::unequipArmor){
		h->checkInventory();
		cout << "Type the name of the armor you want to unequip: " << endl;
		string name;
		cin >> name;
		class Item *it = h->searchItem(name);
		if(it == NULL) {
			cout << "The armor does not exist" << endl;
			return;
		} else if(!h->isInUse(it)) {
			cout << "The armor is not equipped" << endl;
			return;
		}
		h->unequipWeapon(it);
	} else if(map.heroesOnStore()) {
		if(choice == playerChoices::buy) {
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

	srand(time(NULL));

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
	map.setNumHeroesAndMonsters(num_heroes);
	for(int i = 0; i < num_heroes; ++i) {
		struct livingInfo_t livingInfo = {"", 7, defaultData.initialHealthPower, defaultData.initialHealthPower, 1};
		cout << "Type the name of the hero " << i + 1 << ": ";
		cin >> livingInfo.name;

		string heroClass;
		size_t j;
		struct heroInfo_t tempInfo = defaultData.heroInfo;
		while(true) {
			cout << "Type the class you want this hero to have: ";
			cin >> heroClass;
			if(heroClass == "Warrior") {
				tempInfo.strength = defaultData.warriorInfo.strength;
				tempInfo.dexterity = defaultData.warriorInfo.dexterity;
				j = 0;
				break;
			} else if(heroClass == "Paladin") {
				tempInfo.strength = defaultData.paladinInfo.strength;
				tempInfo.agility = defaultData.paladinInfo.agility;
				j = 1;
				break;
			} else if(heroClass == "Sorcerer") {
				tempInfo.dexterity = defaultData.sorcererInfo.dexterity;
				tempInfo.agility = defaultData.sorcererInfo.agility;
				j = 2;
				break;
			} else {
				cout << "That hero class does not exist" << endl;
			}
		}
		map.createHero(livingInfo, tempInfo, j);
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
		cout << "Equip Armor: 8" << endl;
		cout << "Unequip Armor: 9" << endl;
		if(map.heroesOnStore()) {
			cout << "Check items available on the store: 10" << endl;
			cout << "Buy something: 11" << endl;
			cout << "Sell something: 12" << endl;
		}
		cout << "What do you want to do? ";
		cin >> choice;

		if(choice > 12) {
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
			if (choice == -1) { continue; }
			else if(choice < 0 || choice > 3) {
				cout << "Not a valid choice" << endl;
				continue;
			} if (!map.moveHeroes(choice)) {
				cout << "You can't go there!" << endl;
			}

			// compute probability of getting into a fight


			// TODO(stefanos): Could not get this value
			// read from a file.
			float p = 0.3;
			float x = rand() / ((float) RAND_MAX);

			// TODO(stefanos): Test code where in every square
			// there is a fight.
			// In release version, revert this back to using
			// probability
			//if(x <= p) {
			cout << "FIGHT!!!!!!!!" << endl;
			map.generateMonsters(defaultData);

			bool fightContinues = true;
			for (uint32_t i = 0; i < num_heroes; ++i) {
				class Hero *h = map.searchHero(i);
				class Monster *m = map.searchMonster(i);
				h->printInfo();
				cout << endl;
				m->printInfo();
				cout << endl;
			}

			while (fightContinues) {
				for (uint32_t i = 0; i < num_heroes; ++i) {

					class Hero *h;
					class Monster *m;


					//// Hero attack ////
					cout << "Hero " << i + 1 << " attacks" << endl;
					h = map.searchHero(i);
					cout << "Attack Damage: " << h->getAttackDamage() << endl;
					// TODO(stefanos): Let the user decide which monster to hit:DONE
					int32_t option;

					do {
						cout << "Give which monster you want to hit" << endl;
						cin >> option;
						cout << option << endl;
					} while(option < 0 || option>(num_heroes - 1));

					m = map.searchMonster((uint32_t)option);

					while(true) {
						cout << "Choose option:" << endl << "Attack(0) Spell(1) Potion(2)" << endl;
						cin >> option;
						// TODO(stefanos): Take agility into consideration
						if (option == 0) {
							m->receiveAttack(h->getAttackDamage());
							break;
						} else if (option == 1) {
							string spellName;
							cout << "Type the name of the spell you want to use" << endl;
							cin >> spellName;
							class Spell *s = h->searchItem(spellName);
							if(s == NULL) {
								cout << "This spell does not exist" << endl;
								continue;
							}
							if(h->getLevel() < s->getMinLevel()) {
								cout << "You are not on the required level to use this spell" << endl;
								continue;
							}
							if(!h->executeSpell(s, m)) {
								cout << "You don't have enough magic power to execute this spell" << endl;
								continue;
							}
							break;
						} else if (option == 2) {
							//h->usePotion("mySpell");
							//break;
						} else {
							cout << "Not proper option" << endl;
						}
					}

					m->printInfo();
					cout << endl;

					//// Monster attack ////
					cout << "Monster " << i+1 << " attacks" << endl;
					m = map.searchMonster(i);
					uint32_t damage = m->getAttackDamage();
					cout << "Attack Damage: " << damage << endl;
					h = map.searchHero(i);
					h->receiveAttack(damage);
					h->printInfo();
					cout << endl;
				}

				if (map.allHeroesDead()) {
					fightContinues = false;
					cout << endl;
					cout << endl;
					cout << "MONSTERS WON" << endl;
					cout << endl;
					cout << endl;
				} else if (map.allMonstersDead()) {
					fightContinues = false;
					cout << endl;
					cout << endl;
					cout << "HEROES WON" << endl;
					cout << endl;
					cout << endl;
				}
			}
			map.freeMonsters();
			// TODO(stefanos): Free monster memory
		} else if(map.heroesOnStore() && choice == playerChoices::checkStoreItems) {
			store.print();
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

			cout << "CHOICE: " << choice << endl;

			handleHeroSpecificChoices(choice, h, store, map);
		}
	}
	
	return 0;
}
