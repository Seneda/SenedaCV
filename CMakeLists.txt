cmake_minimum_required(VERSION 3.5)
project(SenedaCV)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        cv/img.cpp
        cv/img.hpp
        cv/kernel.cpp
        cv/kernel.hpp
    output.ppm
        cv/ppm.cpp
        cv/ppm.hpp
    read_write_ppm.cpp)

add_executable(SenedaCV ${SOURCE_FILES})