#ifndef LIVING_H
#define LIVING_H

#include <string>

struct livingInfo_t {
	std::string name;
	uint8_t level;
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

	void getLevel(void) const {
		return livingInfo.level;
	}

	void add_level(uint8_t lev){
		livingInfo.level+=lev;
	}
	void set_health(uint32_t num){
		livingInfo.healthPower+=num;
	}
	void set_name(std::string nam){
		livingInfo.name=nam;
	}
};

#endif
