#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <random>

#include "cycle.h"
#include "my_vector.h"
#include "fibonacci.h"

size_t sizes[]{1000, 10000, 50000, 100000, 200000, 500000, 1000000};
size_t times = 5;
unsigned n1[]{1, 2, 5, 10, 15, 20, 25, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
unsigned n2[]{1, 2, 5, 8, 10, 12, 15, 18, 20, 25, 30, 35, 40, 45, 50};

random_device rnd_device;
mt19937 mersenne_engine{rnd_device()}; // Generates random integers
uniform_int_distribution<int> dist{1, 10000};

int gen()
{
    return dist(mersenne_engine);
}

using testing::Eq;

TEST(test_1, max)
{
    MyVector<int> v;

    EXPECT_THROW(v.max(), EmptyVector);

    v.push_back(4);
    v.push_back(33);
    v.push_back(14);
    v.push_back(18);
    v.push_back(45);
    v.push_back(33);
    EXPECT_EQ(45, v.max());

    v.push_back(85);
    EXPECT_EQ(85, v.max());

    // for (size_t size : sizes)
    // {
    //     v.getValues().clear();
    //     v.getValues().resize(size);
    //     fill(v.getValues().begin(), v.getValues().begin() + size, 0);
    //     v.push_back(1);

    //     cout << "max (size " << size << ") t[] =";

    //     for (size_t i = 0; i < times; i++)
    //     {
    //         random_shuffle(v.getValues().begin(), v.getValues().end());

    //         ticks tstart, tend, t;
    //         tstart = getticks();
    //         v.max();
    //         tend = getticks();
    //         t = tend - tstart;

    //         cout << ", " << t;
    //     }
    //     cout << endl;
    // }
}

TEST(test_1, hasDuplicates)
{
    MyVector<int> v;

    v.push_back(4);
    v.push_back(33);
    v.push_back(14);
    v.push_back(18);
    v.push_back(45);
    EXPECT_EQ(false, v.hasDuplicates());

    v.push_back(33);
    EXPECT_EQ(true, v.hasDuplicates());

    // for (size_t size : sizes)
    // {
    //     v.getValues().clear();
    //     v.getValues().resize(size);

    //     cout << "hasDuplicates (size " << size << ") t[] =";

    //     for (size_t i = 0; i < times; i++)
    //     {
    //         generate(v.getValues().begin(), v.getValues().end(), gen);

    //         ticks tstart, tend, t;
    //         tstart = getticks();
    //         v.hasDuplicates();
    //         tend = getticks();
    //         t = tend - tstart;

    //         cout << ", " << t;
    //     }
    //     cout << endl;
    // }
}

TEST(test_1, removeDuplicates)
{
    MyVector<int> v;

    v.push_back(4);
    v.push_back(33);
    v.push_back(14);
    v.push_back(18);
    v.push_back(45);
    v.push_back(10);

    v.removeDuplicates();
    vector<int> vx = v.getValues();
    EXPECT_EQ(6, vx.size());
    EXPECT_EQ(4, vx[0]);
    EXPECT_EQ(18, vx[3]);

    v.push_back(33);
    v.push_back(20);
    v.push_back(18);
    v.removeDuplicates();
    vx = v.getValues();
    EXPECT_EQ(7, vx.size());
    EXPECT_EQ(4, vx[0]);
    EXPECT_EQ(33, vx[1]);
    EXPECT_EQ(18, vx[3]);
    EXPECT_EQ(20, vx[6]);

    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(44);
    v.removeDuplicates();
    vx = v.getValues();
    EXPECT_EQ(8, vx.size());
    EXPECT_EQ(4, vx[0]);
    EXPECT_EQ(18, vx[3]);
    EXPECT_EQ(20, vx[6]);
    EXPECT_EQ(44, vx[7]);

    // for (size_t size : sizes)
    // {
    //     cout << "removeDuplicates (size " << size << ") t[] =";

    //     for (size_t i = 0; i < times; i++)
    //     {
    //         v.getValues().clear();
    //         v.getValues().resize(size);
    //         generate(v.getValues().begin(), v.getValues().end(), gen);

    //         ticks tstart, tend, t;
    //         tstart = getticks();
    //         v.removeDuplicates();
    //         tend = getticks();
    //         t = tend - tstart;

    //         cout << ", " << t;
    //     }
    //     cout << endl;
    // }
}

TEST(test_2, fibonacci_1)
{
    EXPECT_EQ(0, fibonacci_1(0));
    EXPECT_EQ(1, fibonacci_1(1));
    EXPECT_EQ(1, fibonacci_1(2));
    EXPECT_EQ(13, fibonacci_1(7));
    EXPECT_EQ(144, fibonacci_1(12));
    EXPECT_EQ(2584, fibonacci_1(18));

    // for (unsigned n : n1)
    // {
    //     cout << "fibonacci_1 (n " << n << ") t[] =";

    //     for (size_t i = 0; i < times; i++)
    //     {
    //         ticks tstart, tend, t;
    //         tstart = getticks();
    //         fibonacci_1(n);
    //         tend = getticks();
    //         t = tend - tstart;

    //         cout << ", " << t;
    //     }
    //     cout << endl;
    // }
}

TEST(test_2, fibonacci_2)
{
    EXPECT_EQ(0, fibonacci_2(0));
    EXPECT_EQ(1, fibonacci_2(1));
    EXPECT_EQ(1, fibonacci_2(2));
    EXPECT_EQ(13, fibonacci_2(7));
    EXPECT_EQ(144, fibonacci_2(12));
    EXPECT_EQ(2584, fibonacci_2(18));

    // for (unsigned n : n2)
    // {
    //     cout << "fibonacci_2 (n " << n << ") t[] =";

    //     for (size_t i = 0; i < times; i++)
    //     {
    //         ticks tstart, tend, t;
    //         tstart = getticks();
    //         fibonacci_2(n);
    //         tend = getticks();
    //         t = tend - tstart;

    //         cout << ", " << t;
    //     }
    //     cout << endl;
    // }
}
