#ifndef LIVING_H
#define LIVING_H

#include <string>

struct livingInfo_t {
	std::string name;
	uint8_t level;
	uint32_t healthPower;
	bool awake;
};

class Living {
private:
	struct livingInfo_t livingInfo;
public:
	Living(const struct livingInfo_t& info) : livingInfo(info) { }
};

#endif
