# AED 2021/2022 - Aula Pratica 09
# Pedro Ribeiro (DCC/FCUP) [03/01/2022]

cmake_minimum_required(VERSION 3.10)
project(aed2122_p09)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("../googletest" "./googletest")
include_directories("../googletest/googletest/include")
include_directories("../googletest/googlemock/include")

add_executable(aed2122_p09 main.cpp Tests/tests.cpp Tests/funWithGraphs.cpp Tests/graph.cpp)

target_link_libraries(aed2122_p09 gtest gtest_main)
