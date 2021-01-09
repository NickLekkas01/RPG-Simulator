#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <cstdint>
#include "Living.h"

struct monsterInfo_t {
	uint32_t damage[2];
	uint32_t armor;
	uint32_t agility;
};

class Monster : public Living {
private:
	struct monsterInfo_t monsterInfo;
public:
	Monster(const struct livingInfo_t&, const struct monsterInfo_t&);

	void receiveAttack(uint32_t) ;

	void getStats(uint32_t& , uint32_t&, uint32_t&) const ;

	void setStats(uint32_t, uint32_t, uint32_t) ;

	uint32_t getAttackDamage() const;

	bool willGetAttacked(void) const ;

	void regenerate(uint32_t ) ;


	void printInfo(void) const ;
};

#endif
