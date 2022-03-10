#include "funSortProblem.h"

#include <algorithm>
#include <list>

FunSortProblem::FunSortProblem() {}

//-----------------------------------------------------------------

// a)
// T(n) = O(n log n)
// S(n) = O(1)
void FunSortProblem::expressLane(vector<Product> &products, unsigned k) {
    // O(n log n)
    std::sort(products.begin(), products.end(),
              [&](const Product &first, const Product &second) {
                  if (first.getPrice() == second.getPrice())
                      return first.getWeight() < second.getWeight();
                  return first.getPrice() < second.getPrice();
              });

    // O(n - k)
    if (k < products.size())
        products.erase(products.begin() + k, products.end());
}

// b)
// T(n) = O(n log n)
// S(n) = O(n)
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {
    if (values.size() < nc)
        return -1;

    // O(n)
    auto tmp{values};
    unsigned m{INT32_MAX};

    // O(n log n)
    std::sort(tmp.begin(), tmp.end());

    // O(n - nc)
    for (auto i{tmp.begin()}, j{i + nc - 1}, end{tmp.end()}; j < end; ++i, ++j)
        m = min(m, *j - *i);

    return m;
}

// TODO
unsigned FunSortProblem::minPlatforms(const vector<float> &arrival,
                                      const vector<float> &departure) {
    return 0;
}

// TODO
void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {}
