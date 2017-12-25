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
    Item *Inventory;
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
         //InventoryInfo.Inventory=new Item[10];
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
	/*
    uint32_t buy(Item *StoreInventory,uint32_t currentItems,uint32_t size){
        uint32_t option;
        char option2;
        std::cout<<"So you're here to buy"<<std::endl;
        std::cout<<"We have the best weapons and the best potions you can find"<<std::endl;
        print(StoreInventory,currentItems);
        while(1) {
            std::cout << "Which Item would you need?" << std::endl;
            std::cin >> option;
            if (option >currentItems || option<0 ) {
                std::cout << "Item not existing" << std::endl;
                continue;
            }
            else{
                if(InventoryInfo.currently_holding<InventoryInfo.size) {
                    InventoryInfo.currently_holding++;
                }
                else{
                    std::cout<<"Inventory full"<<std::endl;
                    return currentItems;
                }
                currentItems--;
                InventoryInfo.Inventory[InventoryInfo.currently_holding]=StoreInventory[option];
                std::cout<<"Do you want to buy something else?(y/n)"<<std::endl;
                std::cin>>option2;
                if(option2=='y'){
                    continue;
                }
                else{
                    break;
                }
            }
        }
        std::cout<<"Thank you for your visit"<<std::endl;
        return currentItems;
    }
    uint32_t sell(Item *StoreInventory,uint32_t currentItems,uint32_t size){
        uint32_t option;
        char option2;
        std::cout<<"So you're here to sell"<<std::endl;
        std::cout<<"Let's see how valuable your things are"<<std::endl;
        while(1) {
            std::cout << "Which Item would you need to sell?" << std::endl;
            std::cin >> option;
            if (option >InventoryInfo.currently_holding || option<0 ) {
                std::cout << "Item not existing" << std::endl;
                continue;
            }
            else{
                if(InventoryInfo.currently_holding>0 && currentItems<size) {
                    currentItems++;
                    StoreInventory[currentItems]=InventoryInfo.Inventory[option];
                    InventoryInfo.currently_holding--;
                }
                else if(InventoryInfo.currently_holding == 0){
                    std::cout<<"No items holding"<<std::endl;
                    return currentItems;
                }
                else if(currentItems == size){
                    std::cout<<"Store full"<<std::endl;
                    return currentItems;
                }
                std::cout<<"Do you want to sell something else?(y/n)"<<std::endl;
                std::cin>>option2;
                if(option2=='y'){
                    continue;
                }
                else{
                    break;
                }
            }
        }
        std::cout<<"Thank you for your visit"<<std::endl;
        return currentItems;
    }
    void print(Item *StoreInventory,uint32_t size){
        std::cout<<"N . NAME     PRICE      MINIMUM LEVEL   "<<std::endl;
        for(int i = 0; i < size; i++ ){
            std::cout<<i<<". "<<StoreInventory[i].get_name()<<" "<<StoreInventory[i].get_price()<<" "<<StoreInventory[i].get_minimumLevel()<<std::endl;
        }
    }
	*/

};

#endif
