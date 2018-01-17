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

struct spell_record {
	class Spell *s;
	uint32_t roundsRemaining;
};

const uint32_t numberOfSpells = 10;
uint32_t numHeroes;

namespace playerChoices {
	const uint32_t initializeHeroes = 2;
	enum { quit, printMap, moveHeroes, checkInventory, heroInfo, usePotion, equipWeapon,
		unequipWeapon, equipArmor, unequipArmor, checkStoreItems, buy, sell};
};

void usePotion(class Hero *h, class Store& store) {
	h->printPotions();

	// Search potion by name on hero's inventory.
	// If we can't use it, output error messages, otherwise
	// remove it from the store.
	cout << "Type the name of the potion (or go back: -1): " << endl;
	string name;
	cin >> name;
	if(name == "-1")
		return;
	class Potion *potion = (class Potion *) h->usePotion(name);
	if(potion == NULL) {
		cout << "The potion either does not exist, or you are " \
			"not in the required level to use it" << endl;
		return;
	}
	if(h->getLevel() < potion->getMinLevel()) {
		cout << "You are not on the required level to use this potion" << endl;
		return;
	} else {
		store.deleteItem(potion);
	}

	cout << h->getName() << "'s " << potion->getStatName() << " was increased to: " << h->getHealthPower() << endl;
}


void handleHeroSpecificChoices(int32_t choice, class Hero *h, class Store& store, class Map& map) {

	if(choice == playerChoices::checkInventory) {
		h->checkInventory();
	} else if(choice == playerChoices::heroInfo) {
		h->printInfo();
	} else if(choice == playerChoices::usePotion) {
		usePotion(h, store);
	} else if(choice == playerChoices::equipWeapon) {
		if(h->isInventoryEmpty()) {
			cout << "There is nothing to equip" << endl;
			return;
		}
		h->printWeapons();


		// Search weapon by name on hero's inventory and try to eqeuip.
		// If it fails, output error messages.
		cout << "Type the name of the weapon you want to equip (or go back: -1): " << endl;
		string name;
		cin >> name;
		if(name == "-1")
			return;
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

		// Search weapon by name on hero's inventory and try to uneqeuip.
		// If it fails, output error messages.
		cout << "Type the name of the weapon you want to unequip (or go back: -1): " << endl;
		string name;
		cin >> name;
		if(name == "-1")
			return;
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


		// Search armor by name on hero's inventory and try to eqeuip.
		// If it fails, output error messages.
		cout << "Type the name of the armor you want to equip (or go back: -1): " << endl;
		string name;
		cin >> name;
		if(name == "-1")
			return;
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

		// Search armor by name on hero's inventory and try to uneqeuip.
		// If it fails, output error messages.
		cout << "Type the name of the armor you want to unequip (or go back: -1): " << endl;
		string name;
		cin >> name;
		if(name == "-1")
			return;
		class Item *it = h->searchItem(name);
		if(it == NULL) {
			cout << "The armor does not exist" << endl;
			return;
		} else if(!h->isInUse(it)) {
			cout << "The armor is not equipped" << endl;
			return;
		}
		h->unequipWeapon(it);
	} else if(map.heroesOnStore()) {      // If heroes are on the store square, we
	                                      // have some more choices.
		if(choice == playerChoices::buy) {
			if(!h->inventoryAvaiableSpace()) {
				cout << "Not enough space on the inventory" << endl;
				return;
			}

			store.print();

			
			// Search the item by name on the store.
			// If it is possible, buy it for the hero, otherwise
			// output error messages.
			string name;
			cout << "Type the name of the item you want to buy (or go back: -1): ";
			cin >> name;
			if(name == "-1")
				return;
			class Item *it = store.searchItem(name);
			if(it == NULL) {
				cout << "That item is not on the store" << endl;
				return;
			}
			if(!h->hasEnoughMoney(it)) {
				cout << "You don't have enough money to buy this item" << endl;
				return;
			}
			store.removeItem(it);
			h->buy(it);
		} else if(choice == playerChoices::sell) {
	        // NOTE(stefanos): The procedure is the same with the buy,
	        // just for the store now. Notice, that all the items that
	        // players have, come from the store. So, it's impossible
	        // for the store to not have space, so we don't check that.

	        // Show the items that they already have
	        h->checkInventory();
	        string name;
	        cout << "Type the name of the item you want to sell (or go back: -1): ";
	        cin >> name;
			if(name == "-1")
				return;

			///  Try to search the item in the hero's inventory
			///  by name, and output error messages if it can't be sold.
			///  Otherwise, remove it from the store. 
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

void printPreFightInfo(const class Map& map) {
	for (uint32_t i = 0; i < numHeroes; ++i) {
		class Hero *h = map.searchHero(i);
		class Monster *m = map.searchMonster(i);
		h->printInfo();
		cout << endl;
		m->printInfo();
		cout << endl;
	}
}

void useSpell(uint32_t i, struct spell_record spellsActivated[3][numberOfSpells], class Hero *h, class Monster *m) {
	// TODO(stefanos): Think about mana
	// after the end of a fight.

	///  Ask the user for the name of the spell
	string spellName;
	cout << "Type the name of the spell you want to use" << endl;
	cin >> spellName;

	///  Try to find the spell and output error messages
	///  if the hero can't use it.
	class Spell *s = (class Spell *) h->searchItem(spellName);
	if(s == NULL) {
		cout << "This spell does not exist" << endl;
		return;
	}
	if(h->getLevel() < s->getMinLevel()) {
		cout << "You are not on the required level to use this spell" << endl;
		return;
	}

	///  Get the damage of the spell (if 0, we don't have enough mana)
	uint32_t spellDam = h->getCastSpellDamage(s);
	if(!spellDam) {
		cout << "You don't have enough magic power to execute this spell" << endl;
		return;
	}
	// TODO(stefanos): Output info for spell's attack
	// Hit the monster with this damage.
	m->receiveAttack(spellDam);
	
	
	///  Find an empty position for already activated
	///  spells, to put this spell record.
	size_t j;
	for(j = 0; j < numberOfSpells; ++j) {
		if(spellsActivated[i][j].s == NULL)
			break;
	}
	spellsActivated[i][j].s = s;
	spellsActivated[i][j].roundsRemaining = s->getRounds();

	///  Reduce the stats
	uint32_t highDamage, armor, agility;
	// NOTE(stefanos): These are passed as references. No pointers
	// for you C++ people!
	m->getStats(highDamage, armor, agility);
	string statChanged = s->reduceStats(highDamage, armor, agility);
	uint32_t reductionAmount = s->getReductionAmount();

	m->setStats(highDamage, armor, agility);
	cout << m->getName() << "'s " << statChanged << " was reduced by " << reductionAmount << endl;
}

void handleHeroFight(uint32_t i, class Hero *h, class Monster *m, struct spell_record spellsActivated[3][numberOfSpells]) {
	int32_t option;
	while(true) {
		cout << "Choose option:" << endl << "Attack(0) Spell(1) Go Back(-1)" << endl;
		cin >> option;

		if(option == 0 || option == 1) {   // It will attack with one of the two ways

			///  Check if 'm' monster will get attacked.
			if(!m->willGetAttacked()) {
				cout << "Monster avoided the attack" << endl;
				break;
			}
		}
		if(option == -1)
			break;
		else if(option == 0) {
			cout << "Hero attack damage: " << h->getAttackDamage() << endl;
			m->receiveAttack(h->getAttackDamage());

			///  Output messages for the outcome of hero's attack
			if(m->isAwake())
				cout << m->getName() << "'s health is now: " << m->getHealthPower() << endl;
			else
				cout << m->getName() << " died!" << endl;
			break;
		} else if(option == 1) {
			useSpell(i, spellsActivated, h, m);
		} else {
			cout << "Not a proper option" << endl;
		}
	}
	cout << endl;
}

void handleHeroTurn(uint32_t i, class Hero *h, class Store& store, const class Map& map, struct spell_record spellsActivated[3][numberOfSpells]) {
	cout << "Hero's " << i + 1 << " turn" << endl;

	int32_t option;
	while(true) {
		cout << "Choose option:" << endl << "Fight(0) use Potion(1) display Stats (2)" << endl;
		cin >> option;
		if(option == 2) {

			// Choose whose stats you want to display
			cout << "Display Hero Info(0) Display Monster Info(1): " << endl;
			cin >> option;
			if(option == 0)    // display ith's hero info
				h->printInfo();
			else {

				///  Ask for which monster the play wants
				///  to see stats.
				do {
					cout << "Which monster's stats you want to see? ";
					cin >> option;
				} while(option < 0 || option > (numHeroes - 1));
				class Monster *m = map.searchMonster((uint32_t) option);
				m->printInfo();
			}
		} else if(option == 1) {
			usePotion(h, store);
			break;
		} else if(option == 0) {
			do {
				cout << "Give which monster you want to hit" << endl;
				cin >> option;
			} while(option < 0 || option > (numHeroes - 1));
		
			class Monster *m = map.searchMonster((uint32_t)option);
			handleHeroFight(i, h, m, spellsActivated);
		} else {
			cout << "Not a proper option" << endl;
		}
	}
}

void handleMonsterTurn(uint32_t i, class Monster *m, const class Map& map) {
	cout << "Monster " << i+1 << " attacks" << endl;

	///  Get the damage the ith monster does (a number inside its 
	///  damage range)
	uint32_t damage = m->getAttackDamage();
	cout << "Attack Damage: " << damage << endl;


	///  Search heroes to find an alive hero
	///  to hit
	size_t j = i;
	class Hero *h;
	while(j < 3) {   // loop heroes
		if((h = map.searchHero(j))->isAwake())
			break;
		++j;
		if(j == 3)
			j = 0;
	}

	///  Check if the hero will be attacked
	///  based on his agility
	if(h->willGetAttacked()) {

		///  Decrease his health and/or armor based
		///  on the damage computed above.
		h->receiveAttack(damage);


		///  Output messages for the outcome of monster's
		///  attack
		if(h->isAwake())
			cout << h->getName() << "'s health is now: " << h->getHealthPower() << endl;
		else
			cout << h->getName() << " died!" << endl;
		cout << endl;
	} else {
		cout << "Hero avoided the attack" << endl;
	}
}

void handleRoundEnd(class Map& map, struct spell_record spellsActivated[3][numberOfSpells]) {
	for(int j = 0; j < 3; ++j) {   // loop monsters
		for(int k = 0; k < numberOfSpells; ++k) {   // loop spells
			int temp;
			if((temp = spellsActivated[j][k].roundsRemaining) > 0) {  // a spell is still active
				--temp;    // a round just passed
				spellsActivated[j][k].roundsRemaining = temp;
				if(temp == 0) {   // spell just ended - restore back the stats
					///  Restore the stats
					class Monster *m = map.searchMonster(j);
					class Spell *s = spellsActivated[j][k].s;
					uint32_t highDamage, armor, agility;
					// NOTE(stefanos): These are passed as references. No pointers
					// for you C++ people!
					m->getStats(highDamage, armor, agility);
					// TODO(stefanos): Maybe request the stat that was restored here?
					s->restoreStats(highDamage, armor, agility);

					m->setStats(highDamage, armor, agility);

					cout << "End of Spell" << endl;
				}
			}
		}
	}

	// TODO(stefanos): Constant values for now.
	// Should be part of the input file
	map.roundEnd(20, 25);
}


void fight(class Map& map, class Store& store) {
	printPreFightInfo(map);

	// We have 3 monsters at most and each monster can have
	// at most 10 spells activated at a given time.
	struct spell_record spellsActivated[3][numberOfSpells] = { };

	while (true) {
		bool fightEnded = false;

		class Hero *h;
		class Monster *m;
		for (uint32_t i = 0; i < numHeroes; ++i) {
			//// Hero's turn ////
			h = map.searchHero(i);
			if(h->isAwake()) {
				handleHeroTurn(i, h, store, map, spellsActivated);
			}

			// check for end of fight
			if(map.fightEnded()) {
				fightEnded = true;
				break;
			}

			//// Monster's turn ////
			m = map.searchMonster(i);
			if(m->isAwake()) {
				handleMonsterTurn(i, m, map);
			}

			// check for end of fight
			if(!map.fightEnded()) {
				fightEnded = true;
				break;
			}
		}

		if(fightEnded)
			break;


		/////// ROUND END /////////
		handleRoundEnd(map, spellsActivated);
	}

	map.freeMonsters();
}

void initialChoices(bool& Running, class Map& map) {
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

			///  Input the two dimensional position that
			///  the heroes will start.
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
}

void generateHeroes(const defaultData_t& defaultData, class Map& map) {
	for(int i = 0; i < numHeroes; ++i) {
		// TODO(stefanos): Change those debug values
		struct livingInfo_t livingInfo = {"", 7, defaultData.initialHealthPower, defaultData.initialHealthPower, 1};
		cout << "Type the name of the hero " << i + 1 << ": ";
		cin >> livingInfo.name;

		string heroClass;
		size_t j;
		while(true) {
			cout << "Type the class you want this hero to have: ";
			cin >> heroClass;
			if(heroClass == "Warrior") {
				map.createHero(livingInfo, &(defaultData.warriorInfo), 
					heroTypes::Warrior);
				break;
			} else if(heroClass == "Paladin") {
				map.createHero(livingInfo, &(defaultData.paladinInfo), 
					heroTypes::Paladin);
				break;
			} else if(heroClass == "Sorcerer") {
				map.createHero(livingInfo, &(defaultData.sorcererInfo),
					heroTypes::Sorcerer);
				break;
			} else {
				cout << "That hero class does not exist" << endl;
			}
		}
	}
}

void printMainMenuChoices(bool heroesOnStore) {
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
	if(heroesOnStore) {
		cout << "Check items available on the store: 10" << endl;
		cout << "Buy something: 11" << endl;
		cout << "Sell something: 12" << endl;
	}
}

void printMoveChoices() {
	cout << "You can go:" << endl;
	cout << "Up: " << directions::up << endl;
	cout << "Down: " << directions::down << endl;
	cout << "Right: " << directions::right << endl;
	cout << "Left: " << directions::left << endl;
	cout << "Go Back: -1" << endl;
	cout << "Where do you want to go? " << endl;
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
	

	///  Handle the initial 3 choices-loop of the game
	initialChoices(Running, map);

	while(!Running) {
		return 0;
	}

	// Initialize the store
	// NOTE(stefanos): Shared memory for the store. Items getting to the inventory
	// have the memory from the store. Memory gets destroyed when we don't need
	// the store anymore. Provided that any item that any hero has is taken
	// from the store, this is the end of the game.
	
	class Store store;
	// TODO(stefanos): Path relative to the compiler
	// Fix that on the release
	store.readItems("./build/items.dat");

	do {
		cout << "How many heroes do you want (1-3)? " << endl;
		cin >> numHeroes;
	} while(numHeroes < 1 || numHeroes > 3);

	///  Set how many heroes we have (the same number
	///  of monsters will be generated in each fight)
	map.setNumHeroesAndMonsters(numHeroes);

	///  Generate heroes based on default data read from
	///  input file and put them on the map
	generateHeroes(defaultData, map);

	while(Running) {
		
		printMainMenuChoices(map.heroesOnStore());
		int32_t choice;
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

			// Print four choices for movement
			printMoveChoices();


			///////////   Input choice   /////////////
			cin >> choice;
			if (choice == -1) { continue; }
			else if(choice < 0 || choice > 3) {
				cout << "Not a valid choice" << endl;
				continue;
			} if (!map.moveHeroes(choice)) {
				cout << "You can't go there!" << endl;
			}


			///////////   Compute possibility for fight  /////////////
			float possibilityToFight = 0.3;
			float x = rand() / ((float) RAND_MAX);

			if(x > possibilityToFight)  // Will not emerge in fight
				continue;

			cout << "FIGHT!!!!!!!!" << endl;
			map.generateMonsters(defaultData.initialHealthPower);
			fight(map, store);
		} else if(map.heroesOnStore() && choice == playerChoices::checkStoreItems) {
			store.print();
		} else {
			/////////  Choices that are for a specific hero  /////////

			string name;
			cout << "Type the name of the hero you want " \
				"to do this operation for (or go back: -1): " << endl;
			cin >> name;
			if(name == "-1")    // Go back
				continue;

			// Search the hero
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
