# AED 2021/2022 - Aula Pratica 07
# Pedro Ribeiro (DCC/FCUP) [06/12/2012]

cmake_minimum_required(VERSION 3.10)
project(aed2122_p07)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("../googletest" "./googletest")
include_directories("../googletest/googletest/include")
include_directories("../googletest/googlemock/include")

add_executable(aed2122_p07 main.cpp Tests/tests.cpp Tests/funWithBSTs.cpp Tests/bst.h)

target_link_libraries(aed2122_p07 gtest gtest_main)
