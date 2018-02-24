
#include <iostream>
#include <string>
#include "Item.h"

Item::Item(std::string nam, uint32_t pr, uint32_t min_level, itemType type) :
    name(nam), price(pr), minimum_level(min_level), iType(type) { }

Item::Item(const class Item& i) : name(i.name), price(i.price),
    minimum_level(i.minimum_level) { }
                                                
std::string Item::get_name() const{
    return name;
}
int Item::get_price() const{
    return price;
}

itemType Item::getItemType(void) const {
    return iType;
}

uint8_t Item::getMinLevel() const{
    return minimum_level;
}

void Item::print(void) const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Minimum Level: " << minimum_level << std::endl;
}

