#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <cstdint>
#include "Living.h"
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Spell.h"

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
    bool *ItemsUsed;
    uint32_t currently_holding;
    uint32_t size;
};

class Hero : public Living {
private:
	const struct heroInfo_t *const initialData;
    Weapon *hands_availability[2];
	class Armor* armor;
    struct Inventory_t InventoryInfo;

protected:
	struct heroInfo_t heroInfo;
public:
	Hero(const struct livingInfo_t& li, const struct heroInfo_t *const hi) :
	     Living(li), heroInfo(*hi), initialData(hi), armor(NULL) {
         InventoryInfo.size=10;
         InventoryInfo.currently_holding=0;
         InventoryInfo.Inventory=new Item*[10];
         InventoryInfo.ItemsUsed=new bool[InventoryInfo.size];
         for(int i = 0 ; i < InventoryInfo.size ; i++){
             InventoryInfo.ItemsUsed[i]=false;
         }
		 hands_availability[0] = NULL;
		 hands_availability[1] = NULL;
    }
    ~Hero(){
   		delete []InventoryInfo.Inventory;
        delete []InventoryInfo.ItemsUsed;
	}

	virtual void printInfo(void) const {
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
		if(hands_availability[0] == NULL &&
			hands_availability[1] == NULL)
			std::cout << "The hero holds no weapon or spell" << std::endl;
		else if(hands_availability[0] != hands_availability[1]) {
			if(hands_availability[0] != NULL) {
				std::cout << "Hand 1: " << std::endl;
				std::cout << "\t";
 				hands_availability[0]->print();
				std::cout << std::endl;

			}
			if(hands_availability[1] != NULL) {
				std::cout << "Hand 2: " << std::endl;
				std::cout << "\t";
 				hands_availability[1]->print();
				std::cout << std::endl;
			}
		} else {
			std::cout << "The hero holds a two handed weapon: " << std::endl;
			hands_availability[0]->print();
		}
	}

	void regenerate(uint32_t healthToRegen, uint32_t magicPowerToRegen) {
		if(livingInfo.healthPower + healthToRegen <= livingInfo.initialHealthPower)
			livingInfo.healthPower += healthToRegen;
		if(heroInfo.magicPower + magicPowerToRegen <= initialData->magicPower)
			heroInfo.magicPower += magicPowerToRegen;
	}

	void addExp(uint32_t exp) {
		// TODO(stefanos): Possibly add a bound here.
		heroInfo.exp += exp;
	}

	void addMoney(uint32_t m) {
		heroInfo.money += m;
	}

	virtual bool tryLevelUp(void){
		if(heroInfo.exp>100){
			++livingInfo.level;
			return true;
		}
	}


	void receiveAttack(uint32_t opDamage) {
		uint32_t armorValue;
		if(armor != NULL)
			armorValue = armor->getArmor();
		else
			armorValue = 0;
		if(armor != NULL && armorValue > opDamage) {
			armor->decreaseArmor(opDamage);
		} else {
			uint32_t temp = (opDamage - armorValue);
			if(livingInfo.healthPower > temp)
				livingInfo.healthPower -= temp;
			else {
				livingInfo.healthPower = 0;
				livingInfo.awake = false;
			}

			if(armor != NULL)
				armor->resetArmor();
		}
	}

	bool isInventoryEmpty(void) const {
		return (InventoryInfo.currently_holding == 0);
	}

	void printWeapons(void) const {
		std::cout << std::endl;
		std::cout << "Weapons on inventory" << std::endl;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			if(InventoryInfo.Inventory[i]->getItemType() == itemTypes::Weapon) {
				InventoryInfo.Inventory[i]->print();
				std::cout << "In use? " << InventoryInfo.ItemsUsed[i] << std::endl;
			}
		}
		std::cout << std::endl;

	}

	void printArmors(void) const {
		std::cout << std::endl;
		std::cout << "Armors on inventory" << std::endl;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			if(InventoryInfo.Inventory[i]->getItemType() == itemTypes::Armor) {
				InventoryInfo.Inventory[i]->print();
				std::cout << "In use? " << InventoryInfo.ItemsUsed[i] << std::endl;
			}
		}
		std::cout << std::endl;

	}

	void resetHealth(void) {
		livingInfo.healthPower = livingInfo.initialHealthPower;
	}

	void resetHealthToHalf(void) {
		livingInfo.healthPower = livingInfo.initialHealthPower / 2;
	}

	void resetMoneyToHalf(void) {
		heroInfo.money = heroInfo.money / 2;
	}


	uint32_t getAttackDamage(void) {
		uint32_t damage = heroInfo.strength;
		Weapon *weapon1 = hands_availability[0];
		Weapon *weapon2 = hands_availability[1];
		if(weapon1 != NULL) {
			damage += weapon1->get_damage();
			if(weapon1->get_hands() != 2 && weapon2 != NULL) {
				damage += weapon2->get_damage();
			}
		}

		return damage;
	}

	uint32_t getStrength(void) const {
		return heroInfo.strength;
	}

	uint32_t getAgility(void) const {
		return heroInfo.agility;
	}

	bool willGetAttacked(void) const {
		uint32_t x = rand() % 101;
		if(x < heroInfo.agility)
			return false;
		return true;
	}

	uint32_t getMagicPower(void) const {
		return heroInfo.magicPower;
	}

	void reduceMana(uint32_t mana){
		heroInfo.magicPower-=mana;
	}

	uint32_t getCastSpellDamage(class Spell *s) {
		uint32_t mana = s->getMana();
		if(getMagicPower() < mana) {
			return 0;
		}
		uint32_t minDam,maxDam;
		minDam=s->getMinDamage();
		maxDam=s->getMaxDamage();
		reduceMana(mana);
		uint32_t dexterity = heroInfo.dexterity;
		uint32_t temp = rand()%(maxDam-minDam)+minDam;
		uint32_t damage = temp + temp * (getLevel() / ((float) 100))
			+ temp * (dexterity / ((float) 100));
		if(damage  > maxDam)
			damage = maxDam;
		std::cout << "castSpell Damage: " << damage << std::endl;
		return damage;
	}

	void checkInventory(void) const {
		std::cout << std::endl;
		std::cout << "Items on inventory" << std::endl;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			InventoryInfo.Inventory[i]->print();
			if(InventoryInfo.Inventory[i]->getItemType() == itemTypes::Weapon) {
				std::cout << "In use? " << InventoryInfo.ItemsUsed[i] << std::endl;
			}

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

	class Item* searchItem(const std::string& name) {
		for(int i = 0; i < InventoryInfo.currently_holding; ++i)
			if(InventoryInfo.Inventory[i]->get_name() == name) {
				return InventoryInfo.Inventory[i];
			}

		return NULL;
	}

	class Item* usePotion(const std::string& name) {
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {

			if(InventoryInfo.Inventory[i]->getItemType() == itemTypes::Potion && InventoryInfo.Inventory[i]->get_name() == name) {
				class Potion *pot = (class Potion*) InventoryInfo.Inventory[i];
				uint32_t min_lvl = pot->getMinLevel();
				if(livingInfo.level < min_lvl)
					return NULL;

				uint32_t healthPower, strength, dexterity, agility;

				// NOTE(stefanos): These are passed as references, no pointers
				// for you C++ people!
				pot->use(healthPower, strength, dexterity, agility);
				uint32_t restoration_amount = pot->getRestorationAmount();
				if((livingInfo.healthPower = healthPower) > 
					livingInfo.initialHealthPower) {
					livingInfo.healthPower = livingInfo.initialHealthPower;
				}
				heroInfo.strength = strength;
				heroInfo.dexterity = dexterity;
				// TODO(stefanos): Set bound for agility?
				// TODO(stefanos): Set bound for the others also?
				heroInfo.agility = agility;

				class Item *tmp = pot;
				for(int j = i + 1; j<InventoryInfo.currently_holding; j++) {
					InventoryInfo.Inventory[j-1]=InventoryInfo.Inventory[j];
				}
				--InventoryInfo.currently_holding;
				return tmp;
			}
		}

		return NULL;
	}

	bool isInUse(Item *it) {
		if(it->getItemType() == itemTypes::Weapon)
			return (hands_availability[0] == it || hands_availability[1] == it);
		else if(it->getItemType() == itemTypes::Armor)
			return armor == (class Armor *) it;
	}

	bool isOnRequiredLevel(Item *it) {
		return (livingInfo.level >= it->getMinLevel());
	}

	bool equipArmor(class Item *it) {
		if(isInUse(it))
			return false;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			if(InventoryInfo.Inventory[i] == it) {
				InventoryInfo.ItemsUsed[i] = true;
				class Armor *a = (class Armor *) it;
				if(armor != NULL) {
					return false;
				}

				if(livingInfo.level < it->getMinLevel())
					return false;

				armor = a;
			}
		}
		
		return true;
	}

	bool unequipArmor(class Item *it) {
		if(!isInUse(it))
			return false;
		for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
			if(InventoryInfo.Inventory[i] == it) {
				InventoryInfo.ItemsUsed[i] = false;
				if(armor == NULL) {
					return false;
				}

				armor = NULL;
			}
		}
	}

    bool equipWeapon(class Item *it){
		if(isInUse(it))
			return false;
        for(int i = 0; i < InventoryInfo.currently_holding; ++i) {
            if (InventoryInfo.Inventory[i] == it) {
				InventoryInfo.ItemsUsed[i] = true;
				class Weapon *weap = (class Weapon *) InventoryInfo.Inventory[i];
                uint32_t min_lvl = weap->getMinLevel();
                if (livingInfo.level < min_lvl)
                    return false;
                if(hands_availability[0]!=NULL && hands_availability[1]!=NULL) {
                    return false;
                }
                else if((hands_availability[0]==NULL || hands_availability[1]==NULL) && weap->get_hands()==1){
                    if(hands_availability[0]==NULL)
                        hands_availability[0]=weap;
                    else
                        hands_availability[1]=weap;
                }
                else if((hands_availability[0]==NULL && hands_availability[1]==NULL) && weap->get_hands()==2) {
                    hands_availability[0] = weap;
                    hands_availability[1] = weap;
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
				class Weapon *weap = (class Weapon *) InventoryInfo.Inventory[i];
				uint32_t hands = weap->get_hands();
                if((hands_availability[0]==it || hands_availability[1]==it) && hands==1){
                    if(hands_availability[0]==it)
                        hands_availability[0]=NULL;
                    else
                        hands_availability[1]=NULL;
                }
                else if((hands_availability[0]==it && hands_availability[1]==it) && hands==2) {
                    hands_availability[0] = NULL;
                    hands_availability[1] = NULL;
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

	Item *sell(const std::string& name){

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
