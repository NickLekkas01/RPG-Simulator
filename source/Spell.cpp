
#include <string>
#include "Spell.h"
#include "Item.h"


Spell::Spell(std::string nam, uint32_t pr, uint32_t min_level, itemType type,
	uint32_t dmg[2], uint32_t m, uint32_t rAmount, uint32_t rnds) :
	Item(nam, pr, min_level, type), mana(m), reductionAmount(rAmount),
		rounds(rnds) {
	damage[0] = dmg[0];
	damage[1] = dmg[1];
}

	
uint32_t Spell::getReductionAmount(void) const {
	return reductionAmount;
}

uint32_t Spell::getRounds(void) const {
	return rounds;
}

uint32_t Spell::getMinDamage(){
	return damage[0];
}

uint32_t Spell::getMaxDamage(){
	return damage[1];
}

uint32_t Spell::getMana(){
	return mana;
}

void Spell::print(void) const {
	Item::print();
	std::cout << "Damage Low: " << damage[0] << std::endl;
	std::cout << "Damage High: " << damage[1] << std::endl;
	std::cout << "Reduction Amount: " << reductionAmount << std::endl;
	std::cout << "Mana: " << mana << std::endl;
}

