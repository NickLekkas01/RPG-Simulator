#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Hero.h"

using namespace std;

struct defaultData {
	uint32_t initialHealthPower;
	struct heroInfo hinfo;
};

void readDefaultData(const ifstream& file, struct defaultData_t& defaultData) {
	file >> initialHealthPower;
	cout << initialHealthPower << endl;
	string dataClass;
	
	while(file >> dataClass) {
		if(dataClass == "Hero") {
			cout << "Hero Data" << endl;
			file >> defaultData.info.magicPower;
			file >> defaultData.info.strength;
			file >> defaultData.info.dexterity;
			file >> defaultData.info.agility;
			file >> defaultData.info.money;
			file >> defaultData.info.exp;
		}
	}
}

class Living *createLiving(const ifstream& file, struct defaultData cData) {
	cout << "Name: ";
	cin >> 
	if(dataClass == "Hero") {
		cout << "Hero Data" << endl;
		class Hero w(info, heroTypes::Warrior);
		w.printInfo();
	}
}


int main(void) {

	ifstream file("defaultData.dat");
	struct defaultData_t defaultData;
	
	readDefaultData(file, defaultData);
	class Living *h = createLiving(file, defaultData);

	delete h;

	return 0;
}
