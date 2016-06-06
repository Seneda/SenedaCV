cmake_minimum_required(VERSION 3.5)
project(SenedaCV)

add_subdirectory(cv)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        cv/img.cpp
        cv/img.hpp
        cv/kernel.cpp
        cv/kernel.hpp
        cv/ppm.cpp
        cv/ppm.hpp)

set(SCRIPT_FILE
        scripts/apply_filters.cpp)

set(TEST_FILES
        cv/tests/tests.cpp)

add_executable(SenedaCV ${SOURCE_FILES} ${SCRIPT_FILE})
add_executable(SenedaCVTests ${SOURCE_FILES} ${TEST_FILES})
