// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "funWithGraphs.h"
#include "graph.h"

#include <iostream>
#include <vector>

// ----------------------------------------------------------
// Some Example Graphs
// ----------------------------------------------------------

Graph FunWithGraphs::graph1() {
    Graph g(7, false);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 4, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 8);
    g.addEdge(3, 6, 12);
    g.addEdge(3, 7, 11);
    g.addEdge(4, 5, 9);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 10);
    return g;
}

Graph FunWithGraphs::graph2() {
    Graph g(9, false);
    g.addEdge(1, 2, 16);
    g.addEdge(1, 4, 3);
    g.addEdge(1, 5, 8);
    g.addEdge(2, 3, 12);
    g.addEdge(2, 5, 15);
    g.addEdge(2, 6, 1);
    g.addEdge(3, 6, 10);
    g.addEdge(4, 5, 9);
    g.addEdge(4, 7, 7);
    g.addEdge(5, 6, 6);
    g.addEdge(5, 7, 5);
    g.addEdge(5, 8, 2);
    g.addEdge(6, 8, 14);
    g.addEdge(6, 9, 4);
    g.addEdge(7, 8, 13);
    g.addEdge(8, 9, 11);
    return g;
}

Graph FunWithGraphs::graph3() {
    Graph g(11, false);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 7, 1);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 8, 3);
    g.addEdge(3, 8, 3);
    g.addEdge(3, 4, 4);
    g.addEdge(4, 5, 3);
    g.addEdge(4, 6, 1);
    g.addEdge(4, 8, 5);
    g.addEdge(5, 10, 2);
    g.addEdge(6, 10, 3);
    g.addEdge(6, 11, 5);
    g.addEdge(7, 8, 5);
    g.addEdge(7, 9, 2);
    g.addEdge(8, 9, 1);
    g.addEdge(9, 10, 7);
    g.addEdge(9, 11, 3);
    g.addEdge(10, 11, 5);
    return g;
}

Graph FunWithGraphs::graph4() {
    Graph g(4, false);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 3, 5);
    g.addEdge(2, 4, 9);
    g.addEdge(3, 4, 8);
    return g;
}

// ------------------------------------------------------------------------

// ----------------------------------------------------------
// Exercicio 2: Heaps Binários
// ----------------------------------------------------------

// ..............................
// a) Um pequeno jogo
int FunWithGraphs::game(const vector<int> &v) {
    auto digitSum = [&](int a) {
        int sum = 0;

        while (a != 0) {
            sum += a % 10;
            a /= 10;
        }

        return sum;
    };

    MinHeap<int, int> heap(v.size(), -1);

    // O(n)
    for (int a : v)
        heap.insert(a, digitSum(a));

    // O(n log n)
    while (heap.getSize() > 1) {
        int a = heap.removeMin(), b = heap.removeMin();
        int c = abs(a - b);

        heap.insert(c, digitSum(c));
    }

    return heap.removeMin();
}

// ----------------------------------------------------------
// Exercicio 6: Uma cidade "quadriculada"
// ----------------------------------------------------------
// TODO

struct hash_pair final {
    template <class TFirst, class TSecond>
    size_t operator()(const std::pair<TFirst, TSecond> &p) const noexcept {
        uintmax_t hash = std::hash<TFirst>{}(p.first);
        hash <<= sizeof(uintmax_t) * 4;
        hash ^= std::hash<TSecond>{}(p.second);
        return std::hash<uintmax_t>{}(hash);
    }
};

int FunWithGraphs::gridCity(const vector<pair<int, int>> &plants,
                            const vector<pair<int, int>> &houses) {
    int n = plants.size() + houses.size();

    MinHeap<pair<int, int>, int, hash_pair> heap(n, {-1, -1});

    for (const pair<int, int> &h : houses)
        heap.insert(h, INT32_MAX);

    for (const pair<int, int> &p : plants) {
        heap.insert(p, 0);
        heap.decreaseKey(p, 0);
    }

    int distance{0};

    while (heap.getSize() > 0) {
        auto p = heap.removeMinPair();
        auto u = p.first;
        distance += p.second;

        for (const pair<int, int> &h : houses)
            if (u != h)
                heap.decreaseKey(h, abs(u.first - h.first) +
                                        abs(u.second - h.second));
    }

    return distance;
}
