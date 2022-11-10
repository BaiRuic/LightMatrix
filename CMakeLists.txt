cmake_minimum_required(VERSION 3.22)
project(LightMatrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LightMatrix
        LMatrix2.h
        main.cpp)
