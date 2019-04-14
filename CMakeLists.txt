cmake_minimum_required(VERSION 3.9)
project(mmorpg)

set(CMAKE_CXX_STANDARD 11)

add_executable(mmorpg
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
        source/utils.cpp
        source/utils.h
        source/Warrior.h
        source/Weapon.h)
