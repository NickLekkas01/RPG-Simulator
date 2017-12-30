#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <cstdint>
#include "Living.h"
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"

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
	const char *const typeNames[] = { "Warrior", "Sorcerer", "Paladin" };
};

struct heroInfo_t {
	uint32_t magicPower;
	uint32_t strength;
	uint32_t dexterity;
	uint32_t agility;
	uint32_t money;
	uint32_t exp;
    Weapon *hands_availability[2];
};

struct Inventory_t{
    Item **Inventory;
    bool *ItemsUsed;
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
         InventoryInfo.ItemsUsed=new bool[InventoryInfo.size];
         for(int i = 0 ; i < InventoryInfo.size ; i++){
             InventoryInfo.ItemsUsed[i]=false;
         }
		 heroInfo.hands_availability[0] = NULL;
		 heroInfo.hands_availability[1] = NULL;
    }
    ~Hero(){
        delete []InventoryInfo.Inventory;
    }
	void printInfo(void) const {
		std::cout << "Type: " << heroTypes::typeNames[type] << std::endl;
		std::cout << "Name: " << livingInfo.name << std::endl;
		std::cout << "Health Power: " << livingInfo.healthPower << std::endl;
		std::cout << "Level: " << livingInfo.level << std::endl;
		std::cout << "Is Awake? " << livingInfo.awake << std::endl;
		std::cout << "magicPower: " << heroInfo.magicPower << std::endl;
		std::cout << "Strength: "   << heroInfo.strength << std::endl;
		std::cout << "Dexterity: "  << heroInfo.dexterity << std::endl;
		std::cout << "Agility: "    << heroInfo.agility << std::endl;
		std::cout << "Money: "      << heroInfo.money << std::endl;
		std::cout << "Experience: " << heroInfo.exp << std::endl;
		std::cout << "Equipment: " << std::endl;
		if(heroInfo.hands_availability[0] == NULL &&
			heroInfo.hands_availability[1] == NULL)
			std::cout << "The hero holds no weapon or spell" << std::endl;
		else if(heroInfo.hands_availability[0] != heroInfo.hands_availability[1]) {
			if(heroInfo.hands_availability[0] != NULL) {
				std::cout << "Hand 1: " << std::endl;
				std::cout << "\t";
 				heroInfo.hands_availability[0]->print();
				std::cout << std::endl;

			}
			if(heroInfo.hands_availability[1] != NULL) {
				std::cout << "Hand 2: " << std::endl;
				std::cout << "\t";
 				heroInfo.hands_availability[1]->print();
				std::cout << std::endl;
			}
		} else {
			std::cout << "The hero holds a two handed weapon: " << std::endl;
			heroInfo.hands_availability[0]->print();
		}
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

	bool isInventoryEmpty(void) const {
		return (InventoryInfo.currently_holding == 0);
	}

	void checkInventory(void) const {
		std::cout << std::endl;
		std::cout << "Items on inventory" << std::endl;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			InventoryInfo.Inventory[i]->print();
			std::cout << "In use? " << InventoryInfo.ItemsUsed[i] << std::endl;
		}
		std::cout << std::endl;
	}

	void printPotions(void) const {
		std::cout << "Available potions" << std::endl;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			if(InventoryInfo.Inventory[i]->getItemType() == itemTypes::Potion)
				InventoryInfo.Inventory[i]->print();
		}
		std::cout << std::endl;
	}

	class Item* searchItem(std::string name) {
		for(int i = 0; i < InventoryInfo.currently_holding; ++i)
			if(InventoryInfo.Inventory[i]->get_name() == name) {
				return InventoryInfo.Inventory[i];
			}

		return NULL;
	}

	class Item* usePotion(std::string name) {
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			if(InventoryInfo.Inventory[i]->getItemType() == itemTypes::Potion && InventoryInfo.Inventory[i]->get_name() == name) {
				class Potion *pot = (class Potion*) InventoryInfo.Inventory[i];
				uint32_t min_lvl = pot->get_minimumLevel();
				if(livingInfo.level < min_lvl)
					return NULL;
				potionType type = pot->get_Potion_type();
				uint32_t restoration_amount = pot->get_Restoration_amount();
				if(type == potionTypes::health) {
					livingInfo.healthPower += restoration_amount;
				} else if(type == potionTypes::strength) {
					heroInfo.strength += restoration_amount;
				} else if(type == potionTypes::dexterity) {
					heroInfo.dexterity += restoration_amount;
				} else if(type == potionTypes::agility) {
					heroInfo.agility += restoration_amount;
				}

				class Item *tmp = InventoryInfo.Inventory[i];
				for(int j = i + 1; j<InventoryInfo.currently_holding; j++){
					InventoryInfo.Inventory[j-1]=InventoryInfo.Inventory[j];
				}
				--InventoryInfo.currently_holding;
				return tmp;
			}
		}

		return NULL;
	}

	bool isInUse(Item *it) {
		return (heroInfo.hands_availability[0] == it || heroInfo.hands_availability[1] == it);
	}

	bool isOnRequiredLevel(Item *it) {
		return (livingInfo.level >= it->get_minimumLevel());
	}

    bool equipWeapon(class Item *it){
		if(isInUse(it))
			return false;
        for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			// TODO(stefanos): Add a "weapon is currently in use" kind of field to the inventory and mark it here.
            if (InventoryInfo.Inventory[i] == it) {
				InventoryInfo.ItemsUsed[i] = true;
				uint32_t hands;
				if (it->getItemType() == itemTypes::Weapon) {
					class Weapon *weap = (class Weapon *) InventoryInfo.Inventory[i];
					hands = weap->get_hands();
				} else {
					class Spell *spell = (class Spell *) InventoryInfo.Inventory[i];
					hands = spell->get_hands();
				}
                uint32_t min_lvl = weap->get_minimumLevel();
                if (livingInfo.level < min_lvl)
                    return false;
                if(heroInfo.hands_availability[0]!=NULL && heroInfo.hands_availability[1]!=NULL) {
                    return false;
                }
                else if((heroInfo.hands_availability[0]==NULL || heroInfo.hands_availability[1]==NULL) && weap->get_hands()==1){
                    if(heroInfo.hands_availability[0]==NULL)
                        heroInfo.hands_availability[0]=weap;
                    else
                        heroInfo.hands_availability[1]=weap;
                }
                else if((heroInfo.hands_availability[0]==NULL && heroInfo.hands_availability[1]==NULL) && weap->get_hands()==2) {
                    heroInfo.hands_availability[0] = weap;
                    heroInfo.hands_availability[1] = weap;
                }
                else{
                    return false;
                }
            }
        }
        return true;
    }

    bool unequipWeapon(class Item *it){
		if(!isInUse(it))
			return false;
        for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
            if (InventoryInfo.Inventory[i] == it) {
				InventoryInfo.ItemsUsed[i] = false;
				uint32_t hands;
				if (it->getItemType() == itemTypes::Weapon) {
					class Weapon *weap = (class Weapon *) InventoryInfo.Inventory[i];
					hands = weap->get_hands();
				} else {
					class Spell *spell = (class Spell *) InventoryInfo.Inventory[i];
					hands = spell->get_hands();
				}
                if((heroInfo.hands_availability[0]==it || heroInfo.hands_availability[1]==it) && hands==1){
                    if(heroInfo.hands_availability[0]==it)
                        heroInfo.hands_availability[0]=NULL;
                    else
                        heroInfo.hands_availability[1]=NULL;
                }
                else if((heroInfo.hands_availability[0]==it && heroInfo.hands_availability[1]==it) && hands==2) {
                    heroInfo.hands_availability[0] = NULL;
                    heroInfo.hands_availability[1] = NULL;
                }
            }
        }
        return true;
    }


	bool inventoryAvaiableSpace(void) const {
		return (InventoryInfo.currently_holding<InventoryInfo.size);
	}
	bool hasEnoughMoney(class Item* it) const {
		return (heroInfo.money > it->get_price());
	}
	int buy(Item *Item_bought){
		if(inventoryAvaiableSpace()){
            if(hasEnoughMoney(Item_bought)) {
                InventoryInfo.Inventory[InventoryInfo.currently_holding] = Item_bought;
                InventoryInfo.currently_holding++;
                heroInfo.money -= Item_bought->get_price();
                return 1;
            }
            else{
                return 0;
            }
		}
		else{
			return 0;
		}
	}

	Item *sell(std::string name){

		Item *tmp;
        int i;
		for( i = 0; i < InventoryInfo.currently_holding; i++ ){
			if(InventoryInfo.Inventory[i]->get_name()==name){
				tmp=InventoryInfo.Inventory[i];
				for(int j = i + 1; j<InventoryInfo.currently_holding; j++){
					InventoryInfo.Inventory[j-1]=InventoryInfo.Inventory[j];
				}
				break;
			}
		}
        if(i==InventoryInfo.currently_holding){
            return NULL;
        }
		InventoryInfo.currently_holding--;
		heroInfo.money+=tmp->get_price()/2;
		return tmp;
	}
};

#endif
