cmake_minimum_required(VERSION 3.10)
project(aed2122_p04)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("../googletest" "./googletest")
include_directories("../googletest/googletest/include")
include_directories("../googletest/googlemock/include")

add_executable(aed2122_p04 main.cpp Tests/tests.cpp Tests/funSortProblem.cpp Tests/product.cpp Tests/piece.cpp)

target_link_libraries(aed2122_p04 gtest gtest_main)
