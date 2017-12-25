#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
	std::string name;
	int price;
	uint8_t minimum_level;
public:
	std::string get_name() const{
		return name;
	}
	int get_price() const{
		return price;
	}
	uint8_t get_minimumLevel() const{
		return minimum_level;
	}
};

#endif
