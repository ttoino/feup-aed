cmake_minimum_required(VERSION 3.17)
project(feup-aed)

set(CMAKE_CXX_STANDARD 20)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest)
add_subdirectory(${GOOGLETEST_PATH})

file(GLOB TP_FOLDERS CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "TP*")

foreach(tp_folder ${TP_FOLDERS})
    # Add the source files of each TP class
    file(GLOB tp_files CONFIGURE_DEPENDS "${tp_folder}/*.cpp")

    add_executable(${tp_folder} lib/main.cpp ${tp_files})

    target_link_libraries(${tp_folder} gtest_main gmock_main)

endforeach(tp_folder ${TP_FOLDERS})
