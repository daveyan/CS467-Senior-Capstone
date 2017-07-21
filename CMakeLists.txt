cmake_minimum_required(VERSION 3.7)
project(project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES play.cpp Room.hpp Room.cpp Item.hpp Item.cpp Game.hpp Game.cpp)
add_executable(project ${SOURCE_FILES})