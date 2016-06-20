cmake_minimum_required(VERSION 3.5)
project(SenedaCV)

add_subdirectory(cv)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES
        cv/img.cpp
        cv/img.hpp
        cv/kernel.cpp
        cv/kernel.hpp
        cv/ppm.cpp
        cv/ppm.hpp)

set(Apply_Filters
        scripts/apply_filters.cpp)
set(Edge
        scripts/edge.cpp)

set(TEST_FILES
        cv/tests/tests.cpp)

find_package( Threads )

add_executable(SenedaCV ${SOURCE_FILES} ${Apply_Filters})
add_executable(Edge ${SOURCE_FILES} ${Edge})
add_custom_target(EdgeValg valgrind ${SOURCE_FILES} ${Edge})

add_executable(SenedaCVTests ${SOURCE_FILES} ${TEST_FILES})

target_link_libraries( Edge ${CMAKE_THREAD_LIBS_INIT} )
