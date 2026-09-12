cmake_minimum_required(VERSION 4.3)
project(jpeg_copy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(jpeg_copy
        load_image.cpp
        load_image.h)
