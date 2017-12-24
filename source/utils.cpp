#include <string>
#include <cstdint>
#include <istream>
#include "utils.h"

// (stefanos): Any line starting with a #
// is a comment
void skipComments(std::istream& input) {
	char c;
	std::string s;

	while(!input.eof()) {
		c = input.get();
		if(c == '#') {
			getline(input, s);
		} else {
			input.unget();
			return;
		}
	}
}

// (stefanos): Read default data for hero types and monster types.
void readDefaultData(std::istream& input, struct defaultData_t& defaultData) {
	skipComments(input);
	input >> defaultData.initialHealthPower;
	std::string dataClass;
	
	skipComments(input);
	while(input >> dataClass) {
		if(dataClass == "Hero") {
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
		if(dataClass == "Monster") {
			input >> defaultData.monsterInfo.damage[0];
			input >> defaultData.monsterInfo.damage[1];
			input >> defaultData.monsterInfo.armor;
			input >> defaultData.monsterInfo.agility;
		} else if(dataClass == "Dragon") {
			input >> defaultData.dragonInfo.damage[0];
			input >> defaultData.dragonInfo.damage[1];
		} else if(dataClass == "Exoskeleton") {
			input >> defaultData.exoskeletonInfo.armor;
		} else if(dataClass == "Spirit") {
			input >> defaultData.spiritInfo.agility;
		}
	}
}
