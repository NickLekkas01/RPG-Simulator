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
	Living(const struct livingInfo_t& info) : livingInfo(info) { }
	struct livingInfo_t get_livingInfo(){
		return livingInfo;
	}

	uint32_t getLevel(void) const {
		return livingInfo.level;
	}

	bool isAwake(void) const {
		return livingInfo.awake;
	}

	void setAwake(bool state) {
		livingInfo.awake = state;
	}

	std::string getName(void) const {
		return livingInfo.name;
	}

	void addLevel(uint8_t lev){
		livingInfo.level+=lev;
	}
	void addHealth(uint32_t num){
		livingInfo.healthPower+=num;
	}
	void setName(std::string nam){
		livingInfo.name=nam;
	}
};

#endif
