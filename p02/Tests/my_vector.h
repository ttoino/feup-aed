#include <iostream>
#include <vector>

using namespace std;

template <class T> class MyVector {
    vector<T> values;

public:
    MyVector();
    ~MyVector();
    void push_back(T v1);
    vector<T> &getValues();
    T max() const;
    bool hasDuplicates() const;
    void removeDuplicates();
};

// exception EmptyVector
class EmptyVector {};

// methods
template <class T> MyVector<T>::MyVector() {}

template <class T> MyVector<T>::~MyVector() {}

template <class T> void MyVector<T>::push_back(T v1) { values.push_back(v1); }

template <class T> vector<T> &MyVector<T>::getValues() { return values; }

//---------------------------------

// a)
// T(n) = O(n)
// S(n) = O(1)
template <class T> T MyVector<T>::max() const {
    if (values.empty())
        throw EmptyVector();

    T vmax = values.at(0);

    for (const T t : values)
        if (t > vmax)
            vmax = t;

    return vmax;
}

// b)
// T(n) = O(n²)
// S(n) = O(1)
template <class T> bool MyVector<T>::hasDuplicates() const {
    for (auto i = values.begin(), end = values.end(); i < end; i++)
        for (auto j = i + 1; j < end; j++)
            if (*i == *j)
                return true;

    return false;
}

// c)
// T(n) = O(n³) -- not O(n²) because vector::erase is O(n)
// S(n) = O(1)
template <class T> void MyVector<T>::removeDuplicates() {
    for (auto i = values.begin(), end = values.end(); i < end; i++)
        for (auto j = i + 1; j < end; j++)
            if (*i == *j) {
                values.erase(j--);
                end--;
            }
}
