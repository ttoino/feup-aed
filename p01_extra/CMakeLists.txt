cmake_minimum_required(VERSION 3.10)
project(aed2122_p01_extra)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory("../googletest" "./googletest")
include_directories("../googletest/googletest/include")
include_directories("../googletest/googlemock/include")

add_executable(aed2122_p01_extra main.cpp Tests/tests.cpp Tests/mail.cpp Tests/postman.cpp Tests/postOffice.cpp)

target_link_libraries(aed2122_p01_extra gtest gtest_main)
