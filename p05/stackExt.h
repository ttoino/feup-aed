#include <iostream>
#include <stack>
using namespace std;

template <class T> class StackExt {
    stack<T> values;
    stack<T> minimums;

public:
    StackExt(){};
    bool empty() const;
    T &top();
    void pop();
    void push(const T &val);
    T &findMin();
};

// 2)
template <class T> bool StackExt<T>::empty() const { return values.empty(); }

template <class T> T &StackExt<T>::top() { return values.top(); }

template <class T> void StackExt<T>::pop() {
    if (!empty() && top() == findMin())
        minimums.pop();
    values.pop();
}

template <class T> void StackExt<T>::push(const T &val) {
    if (empty() || val <= findMin())
        minimums.push(val);
    values.push(val);
}

template <class T> T &StackExt<T>::findMin() { return minimums.top(); }
