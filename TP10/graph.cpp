// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"
#include <set>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    nodes[src].adj.push_back({src, dest, weight});
    if (!hasDir)
        nodes[dest].adj.push_back({dest, src, weight});
}

// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
int Graph::prim(int r) {
    MinHeap<int, int> heap(n, -1);

    for (int i{1}; i <= n; ++i)
        heap.insert(i, nodes[i].distance = INT32_MAX);

    heap.decreaseKey(r, nodes[r].distance = 0);

    int distance{0};

    while (heap.getSize() > 0) {
        int u = heap.removeMin();

        distance += nodes[u].distance;

        for (const Edge &e : nodes[u].adj)
            if (heap.hasKey(e.dest) && nodes[e.dest].distance > e.weight)
                heap.decreaseKey(e.dest, nodes[e.dest].distance = e.weight);
    }

    return distance;
}

// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
int Graph::kruskal() {
    DisjointSets<int> sets{};

    for (int i{1}; i <= n; ++i)
        sets.makeSet(i);

    std::set<Edge> edges{};

    for (const Node &n : nodes)
        edges.insert(n.adj.begin(), n.adj.end());

    int sum{0};

    for (const Edge &e : edges)
        if (sets.find(e.src) != sets.find(e.dest)) {
            sum += e.weight;
            sets.unite(e.src, e.dest);
        }

    return sum;
}
