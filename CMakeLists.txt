cmake_minimum_required(VERSION 4.3)
project(jpeg_copy)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(jpeg_copy
        load_image.cpp
        load_image.h)
