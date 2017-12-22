#ifndef LIVING_H
#define LIVING_H

#include <string>

struct livingInfo {
	std::string name;
	uint8_t level;
	uint32_t healthPower;
};

class Living {
private:
	struct livingInfo lInfo;
public:
	Living(const struct livingInfo& info) : lInfo(info) { }
};

#endif
