#include "gmock/gmock.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    std::cout << "AED 2021/2022 - Running all tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}