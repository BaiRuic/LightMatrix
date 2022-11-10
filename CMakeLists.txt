cmake_minimum_required(VERSION 3.22)
project(LightMatrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LightMatrix
        src/LMatrix2.h
        src/LMatrix2.cpp
        main.cpp )
