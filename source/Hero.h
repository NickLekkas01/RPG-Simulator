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
	Hero(const struct livingInfo_t&, const struct heroInfo_t *const) ;
    ~Hero();

	virtual void printInfo(void) const ;

	void regenerate(uint32_t, uint32_t) ;

	void addExp(uint32_t);

	void addMoney(uint32_t);

	virtual bool tryLevelUp(void);


	void receiveAttack(uint32_t) ;

	bool isInventoryEmpty(void) const ;

	void printWeapons(void) const ;

	void printArmors(void) const ;

	void resetHealth(void) ;

	void resetHealthToHalf(void) ;

	void resetMoneyToHalf(void) ;


	uint32_t getAttackDamage(void) ;

	uint32_t getStrength(void) const ;

	uint32_t getAgility(void) const ;

	bool willGetAttacked(void) const ;

	uint32_t getMagicPower(void) const;

	void reduceMana(uint32_t);

	uint32_t getCastSpellDamage(class Spell *) ;

	void checkInventory(void) const ;

	void printPotions(void) const ;

	class Item* searchItem(const std::string&) ;

	class Item* usePotion(const std::string&) ;

	bool isInUse(Item *);

	bool isOnRequiredLevel(Item *) ;

	bool equipArmor(class Item *) ;

	bool unequipArmor(class Item *) ;

    bool equipWeapon(class Item *);

    bool unequipWeapon(class Item *);

	bool inventoryAvaiableSpace(void) const;
	bool hasEnoughMoney(class Item*) const ;

	int buy(Item *);

	Item *sell(const std::string&);
};

#endif
