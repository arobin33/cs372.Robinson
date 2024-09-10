cmake_minimum_required(VERSION 3.29)
project(data)

set(CMAKE_CXX_STANDARD 11)

add_executable(data main.cpp
        apps/apptemplate/source/assignment01.cpp
        apps/hanoi/hanoi.cpp
        apps/hanoi/hanoii.cpp)
