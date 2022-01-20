cmake_minimum_required(VERSION 3.10)
project(aed2122_p01)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("../googletest" "./googletest")
include_directories("../googletest/googletest/include")
include_directories("../googletest/googlemock/include")

add_executable(aed2122_p01 main.cpp Tests/tests.cpp Tests/parque.cpp)

target_link_libraries(aed2122_p01 gtest gtest_main)
