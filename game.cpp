#include <iostream>
#include <string>
#include <fstream>
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Hero.h"

using namespace std;

struct defaultData_t {
	uint32_t initialHealthPower;
	struct heroInfo hInfo;
};

void readDefaultData(ifstream& file, struct defaultData_t& defaultData) {
	file >> defaultData.initialHealthPower;
	cout << defaultData.initialHealthPower << endl;
	string dataClass;
	
	while(file >> dataClass) {
		if(dataClass == "Hero") {
			cout << "Hero Data" << endl;
			file >> defaultData.hInfo.magicPower;
			file >> defaultData.hInfo.strength;
			file >> defaultData.hInfo.dexterity;
			file >> defaultData.hInfo.agility;
			file >> defaultData.hInfo.money;
			file >> defaultData.hInfo.exp;
		}
	}
}

class Living *createLiving(ifstream& file, struct defaultData_t& defaultData) {
	struct livingInfo lInfo;
	cout << "Name: ";
	cin >> lInfo.name;
	lInfo.level = 1;
	lInfo.healthPower = lInfo.initialHealthPower = defaultData.initialHealthPower;
	cout << "Hero Data" << endl;
	class Hero *h = new Hero(lInfo, defaultData.hInfo, heroTypes::Warrior);
	h->printInfo();
	return h;
}


int main(void) {

	ifstream file("defaultData.dat");
	struct defaultData_t defaultData;
	
	readDefaultData(file, defaultData);
	class Living *h = createLiving(file, defaultData);

	delete h;

	return 0;
}
