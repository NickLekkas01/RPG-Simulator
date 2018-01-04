cmake_minimum_required(VERSION 3.9)
project(source)

set(CMAKE_CXX_STANDARD 11)

add_executable(source
        Armor.h
        FireSpell.h
        game.cpp
        Hero.h
        IceSpell.h
        Item.h
        Living.h
        Monster.h
        Potion.h
        Spell.h
        utils.cpp
        utils.h
        Warrior.h
        Weapon.h)
