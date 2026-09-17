cmake_minimum_required(VERSION 4.3)
project(jpeg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(jpeg
        main.cpp
        main.h)
