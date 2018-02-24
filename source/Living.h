#ifndef LIVING_H
#define LIVING_H

#include <string>

struct livingInfo_t {
	std::string name;
	uint32_t level;
	uint32_t healthPower;
	uint32_t initialHealthPower;
	bool awake;
};

class Living {
protected:
	struct livingInfo_t livingInfo;
public:
	Living(const struct livingInfo_t&) ;
	struct livingInfo_t get_livingInfo();

	uint32_t getLevel(void) const ;

	bool isAwake(void) const ;

	bool getHealthPower(void) const ;

	void setAwake(bool) ;

	std::string getName(void) const ;

	void addLevel(uint8_t );
	void addHealth(uint32_t);
	void setName(std::string);
};

#endif
