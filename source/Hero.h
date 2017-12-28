#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <cstdint>
#include "Living.h"
#include "Item.h"

struct warriorInfo_t {
	uint32_t strength;
	uint32_t dexterity;
};

struct paladinInfo_t {
	uint32_t strength;
	uint32_t agility;
};

struct sorcererInfo_t {
	uint32_t dexterity;
	uint32_t agility;
};

typedef uint8_t heroType;
// NOTE(stefanos): Changed to avoid linker
// problems
namespace heroTypes {
	const uint8_t Warrior = 0;
	const uint8_t Sorcerer = 1;
	const uint8_t Paladin = 2;
};

struct heroInfo_t {
	uint32_t magicPower;
	uint32_t strength;
	uint32_t dexterity;
	uint32_t agility;
	uint32_t money;
	uint32_t exp;
};

struct Inventory_t{
    Item **Inventory;
    uint32_t currently_holding;
    uint32_t size;
};

class Hero : public Living {
private:
	struct heroInfo_t heroInfo;
	heroType type;
    struct Inventory_t InventoryInfo;
public:
	Hero(const struct livingInfo_t& li, const struct heroInfo_t& hi, heroType t) :
	     Living(li), heroInfo(hi), type(t) {
         InventoryInfo.size=10;
         InventoryInfo.currently_holding=0;
         InventoryInfo.Inventory=new Item*[10];
    }
    ~Hero(){
        delete []InventoryInfo.Inventory;
    }
	void printInfo(void) const {
		std::cout << "magicPower: " << heroInfo.magicPower << std::endl;
		std::cout << "Strength: "   << heroInfo.strength << std::endl;
		std::cout << "Dexterity: "  << heroInfo.dexterity << std::endl;
		std::cout << "Agility: "    << heroInfo.agility << std::endl;
		std::cout << "Money: "      << heroInfo.money << std::endl;
		std::cout << "Experience: " << heroInfo.exp << std::endl;
	}

	// NOTE(stefanos): Explain how the (exp > 100) and (exp = exp - 100)
	// logic works.

	//ΝΟΤΕ(nikos): We'll have an the experience of each player, and by winning a monster he will gain experience. If his experience 
	// passes 100 then he grows one level and the remaining experience is for the next level.
	//Also i used comments in if's because i'm not so sure about how the variable type works ( just type==0  or type==1 or type==2 ?)
	void levelUp(){
		if(heroInfo.exp>100){
			Living::add_level(1);
			if(type==0){
				heroInfo.strength+=2;
				heroInfo.agility+=2;
				heroInfo.dexterity++;
				heroInfo.magicPower+=30;
				Living::set_health(100);
			}
			else if(type==1){
				heroInfo.strength+=2;
				heroInfo.dexterity+=2;
				heroInfo.agility++;
				heroInfo.magicPower+=50;
				Living::set_health(80);
			}
			else if(type==2){
				heroInfo.dexterity+=2;
				heroInfo.agility+=2;
				heroInfo.strength+=1;
				heroInfo.magicPower+=100;
				Living::set_health(50);
			}
			heroInfo.money+=500;
			heroInfo.exp=heroInfo.exp-100;
		}
	}
	int inventoryAvaiableSpace(void) const {
		return (InventoryInfo.currently_holding<InventoryInfo.size);
	}
	int hasEnoughMoney(class Item* it) const {
		return (heroInfo.money > it->get_price());
	}
	int buy(Item *Item_bought){
		if(InventoryInfo.currently_holding<InventoryInfo.size){
			InventoryInfo.currently_holding++;
			InventoryInfo.Inventory[InventoryInfo.currently_holding]=Item_bought;
			return 1;
		}
		else{
			return 0;
		}
	}

	Item *sell(std::string name){
		Item *tmp;
		for(int i = 0; i < InventoryInfo.currently_holding; i++ ){
			if(InventoryInfo.Inventory[i]->get_name()==name){
				tmp=InventoryInfo.Inventory[i];
				for(int j = i + 1; j<InventoryInfo.currently_holding; j++){
					InventoryInfo.Inventory[j-1]=InventoryInfo.Inventory[j];
				}
				break;
			}
		}
		InventoryInfo.currently_holding--;
		return tmp;
	}
};

#endif
