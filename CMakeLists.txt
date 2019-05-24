cmake_minimum_required(VERSION 3.12)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

add_subdirectory(test/googletest)
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

add_executable(untitled2 main.cpp Parser.cpp Parser.h test/ImplementedFeaturesTest.h test/NotImplementedFeaturesTest.h MyParser.cpp MyParser.h WhiteBoxTest.h )
target_link_libraries(untitled2 gtest gtest_main)