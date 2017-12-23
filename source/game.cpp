#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include "Hero.h"
#include "Monster.h"

#define INPUT_FILE_ERROR 1

using namespace std;

// TODO(stefanos): Think if it is better to put
// in warrior, paladin and sorcerer all the info
// and eliminate the hero Info
struct defaultData_t {
	uint32_t initialHealthPower;
	struct heroInfo_t heroInfo;
	struct warriorInfo_t warriorInfo;
	struct paladinInfo_t paladinInfo;
	struct sorcererInfo_t sorcererInfo;
};

// (stefanos): Any line starting with a #
// is a comment
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

// (stefanos): Read default data for hero types and monster types.
void readDefaultData(istream& input, struct defaultData_t& defaultData) {
	skipComments(input);
	input >> defaultData.initialHealthPower;
	cout << defaultData.initialHealthPower << endl;
	string dataClass;
	
	skipComments(input);
	while(input >> dataClass) {
		if(dataClass == "Hero") {
			cout << "Hero Data" << endl;
			input >> defaultData.heroInfo.magicPower;
			input >> defaultData.heroInfo.strength;
			input >> defaultData.heroInfo.dexterity;
			input >> defaultData.heroInfo.agility;
			input >> defaultData.heroInfo.money;
			input >> defaultData.heroInfo.exp;
		} else if(dataClass == "Warrior") {
			input >> defaultData.warriorInfo.strength;
			input >> defaultData.warriorInfo.dexterity;
		} else if(dataClass == "Paladin") {
			input >> defaultData.paladinInfo.strength;
			input >> defaultData.paladinInfo.agility;
		} else if(dataClass == "Sorcerer") {
			input >> defaultData.sorcererInfo.dexterity;
			input >> defaultData.sorcererInfo.agility;
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
	if(!file.good()) {
		cout << "There was a problem opening the data input" << endl;
		return INPUT_FILE_ERROR;
	}

	struct defaultData_t defaultData;
	readDefaultData(file, defaultData);

	return 0;
}
