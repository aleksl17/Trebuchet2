cmake_minimum_required(VERSION 3.3)
project(Trebuchet2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCE_FILES main.cpp)

add_executable(Trebuchet2 ${SOURCE_FILES})

target_link_libraries (Trebuchet2 sfml-graphics sfml-window sfml-system)