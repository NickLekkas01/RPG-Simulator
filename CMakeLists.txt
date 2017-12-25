cmake_minimum_required(VERSION 3.8)
project(mmorpg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        source/Armor.h
        source/FireSpell.h
        source/game.cpp
        source/Hero.h
        source/IceSpell.h
        source/Item.h
        source/Living.h
        source/Monster.h
        source/Potion.h
        source/Spell.h
        source/Warrior.h
        source/Weapon.h)

add_executable(mmorpg ${SOURCE_FILES})