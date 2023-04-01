cmake_minimum_required(VERSION 3.23)
project(week1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(week1
        linklist.cpp
        linklist.h)
