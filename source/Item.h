#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

class Item {
private:
	std::string name;
	uint32_t price;
	uint32_t minimum_level;
public:
	Item(std::string nam, uint32_t pr, uint32_t min_level) :
		name(nam), price(pr), minimum_level(min_level) { }
	
	std::string get_name() const{
		return name;
	}
	int get_price() const{
		return price;
	}
	uint8_t get_minimumLevel() const{
		return minimum_level;
	}

	virtual void print(void) const {
		std::cout << "Name: " << name << std::endl;
		std::cout << "Price: " << price << std::endl;
		std::cout << "Minimum Level: " << minimum_level << std::endl;
	}
};

#endif
