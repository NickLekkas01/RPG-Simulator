#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Hero.h"

#define INPUT_FILE_ERROR 1

using namespace std;

// TODO(stefanos): Think if it is better to put
// in warrior, paladin and sorcerer all the info
// and eliminate the hero Info
struct defaultData_t {
	uint32_t initialHealthPower;
	struct heroInfo hInfo;
	struct warriorInfo wInfo;
	struct paladinInfo pInfo;
	struct sorcererInfo sInfo;
};

void skipComments(istream& input) {
	char c;
	string s;

	while(!input.eof()) {
		c = input.get();
		if(c == '\n')
			return;
		if(c == '#') {
			getline(input, s);
			c = input.get();
		}
	}
}

void readDefaultData(istream& input, struct defaultData_t& defaultData) {
	skipComments(input);
	input >> defaultData.initialHealthPower;
	cout << defaultData.initialHealthPower << endl;
	string dataClass;
	
	skipComments(input);
	while(input >> dataClass) {
		if(dataClass == "Hero") {
			cout << "Hero Data" << endl;
			input >> defaultData.hInfo.magicPower;
			input >> defaultData.hInfo.strength;
			input >> defaultData.hInfo.dexterity;
			input >> defaultData.hInfo.agility;
			input >> defaultData.hInfo.money;
			input >> defaultData.hInfo.exp;
		} else if(dataClass == "Warrior") {
			input >> defaultData.wInfo.strength;
			input >> defaultData.wInfo.dexterity;
		} else if(dataClass == "Paladin") {
			input >> defaultData.wInfo.strength;
			input >> defaultData.wInfo.agility;
		} else if(dataClass == "Sorcerer") {
			input >> defaultData.wInfo.dexterity;
			input >> defaultData.wInfo.agility;
		}
	}
}

/*
TODO(stefanos): Functionality -- To be specified...
class Living *createLiving(istream& input, struct defaultData_t& defaultData) {
	struct livingInfo lInfo;
	cout << "Name: ";
	cin >> lInfo.name;
	lInfo.level = 1;
	lInfo.healthPower = defaultData.initialHealthPower;
	cout << "Hero Data" << endl;
	class Hero *h = new Hero(lInfo, defaultData.hInfo, heroTypes::Warrior);
	h->printInfo();
	return h;
}
*/


int main(void) {
	
	// File location relative to the COMPILER
	// TODO(stefanos): Remove that from the release
	ifstream file("./build/defaultData.dat");
	if(!input.good()) {
		cout << "There was a problem opening the data input" << endl;
		return INPUT_FILE_ERROR;
	}

	struct defaultData_t defaultData;
	readDefaultData(input, defaultData);

	return 0;
}
