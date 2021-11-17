#include "funSearchProblem.h"

FunSearchProblem::FunSearchProblem() {}

//-----------------------------------------------------------------

// a)
/**
 * Returns the number of buildings that see the sun.
 *
 * @param values The height of the buildings.
 */
int FunSearchProblem::facingSun(const vector<int> &values) {
    int highest{0}, count{0};

    for (int v : values) {
        if (v > highest) {
            highest = v;
            count++;
        }
    }

    return count;
}

// b)
/**
 * Calculates the square root of an integer.
 * If it isn't a perfect square, the result is rounded down.
 *
 * @param num The number to calculate the square root of.
 */
int FunSearchProblem::squareR(int num) {
    int min{0}, max{num}, mid{num / 2};

    while (!(min == max - 1 || min == max)) {
        mid = min + (max - min) / 2;

        if (mid * mid > num)
            max = mid;
        else
            min = mid;
    }

    return min;
}

// c)
/**
 * Finds the smallest positive value missing from a vector.
 * Returns 0 if the vector has no positive values.
 *
 * @param values The vector.
 */
int FunSearchProblem::smallestMissingValue(const vector<int> &values) {
    int s{1};
    bool found{false};

    // O(n)
    for (int v : values)
        if (v > 0) {
            found = true;
            break;
        }

    if (!found)
        return 0;

    // O(k * n)
    while (found) {
        found = false;

        for (int v : values)
            if (v == s) {
                found = true;
                s++;
                break;
            }
    }

    return s;
}

// d)
/**
 * Finds the distribution of books by students which has the minimum amount
 * of pages per student. Returns -1 if no distribution is possible, the max
 * amount of pages each student has to read otherwise.
 *
 * @param values How many pages each book has.
 * @param numSt How many students.
 */
int FunSearchProblem::minPages(const vector<int> &values, int numSt) {
    if (values.size() < numSt)
        return -1;

    int low = 0, high = 0;

    for (int value : values) {
        high += value;
        if (value > low)
            low = value;
    }

    while (low < high) {
        int mid = (high + low) / 2;

        int students = 1;
        int s = 0;

        for (int value : values) {
            s += value;
            if (s > mid) {
                s = value;
                students++;
            }
        }

        if (students <= numSt)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}
