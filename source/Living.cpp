#include "Living.h"
#include <string>

	Living::Living(const struct livingInfo_t& info) : livingInfo(info) { }
	struct livingInfo_t Living::get_livingInfo(){
		return livingInfo;
	}

	uint32_t Living::getLevel(void) const {
		return livingInfo.level;
	}

	bool Living::isAwake(void) const {
		return livingInfo.awake;
	}

	bool Living::getHealthPower(void) const {
		return livingInfo.healthPower;
	}

	void Living::setAwake(bool state) {
		livingInfo.awake = state;
	}

	std::string Living::getName(void) const {
		return livingInfo.name;
	}

	void Living::addLevel(uint8_t lev){
		livingInfo.level+=lev;
	}
	void Living::addHealth(uint32_t num){
		livingInfo.healthPower+=num;
	}
	void Living::setName(std::string nam){
		livingInfo.name=nam;
	}

