cmake_minimum_required(VERSION 3.3)
project(Trebuchet2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp
        game.cpp
        game.h
        layers/layer.cpp
        layers/layer.h
        layers/map.cpp
        layers/map.h
        objects/object.cpp
        objects/object.h
        objects/sprite.cpp
        objects/sprite.h
        )

add_executable(Trebuchet2 ${SOURCE_FILES})

target_link_libraries (Trebuchet2 sfml-graphics sfml-window sfml-system jsoncpp)
target_include_directories(Trebuchet2 PUBLIC .)