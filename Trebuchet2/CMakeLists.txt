cmake_minimum_required(VERSION 3.3)
project(Trebuchet2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp
        game.cpp
        game.h
        layer/layer.cpp
        layer/layer.h
        map/map.cpp
        map/map.h
        objects/object.h
        objects/sprite.cpp
        objects/sprite.h
        objects/catapult.h
        player/player.h
        projectile/projectile.cpp
        projectile/projectile.h
        menu/menu.cpp
        menu/menu.h
        menu/death.cpp
        menu/death.h
        menu/select.cpp
        menu/select.h
        menu/victory.cpp
        menu/victory.h)

add_executable(Trebuchet2 ${SOURCE_FILES})

target_link_libraries (Trebuchet2 jsoncpp sfml-graphics sfml-window sfml-system )
target_include_directories(Trebuchet2 PUBLIC .)