// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>
#include <unordered_set>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir)
        nodes[dest].adj.push_back({src, weight});
}

// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
int Graph::dijkstra_distance(int a, int b) {
    MinHeap<int, uint> pq{n, -1};

    for (int i{1}; i <= n; ++i) {
        pq.insert(i, -1);
        nodes[i].dist = INT32_MAX;
    }

    pq.decreaseKey(a, 0);
    nodes[a].dist = 0;

    while (pq.getSize() > 0) {
        auto p = pq.removeMinNode();
        auto &n = nodes[p.key];

        if (p.key == b)
            return p.value;

        for (Edge e : nodes[p.key].adj) {
            Node &o = nodes[e.dest];
            int newdist = e.weight + n.dist;

            if (o.dist > newdist) {
                pq.decreaseKey(e.dest, newdist);
                o.dist = newdist;
                o.pred = p.key;
            }
        }
    }

    return -1;
}

// ..............................
// b) Caminho mais curto entre dois nós
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path{};

    if (dijkstra_distance(a, b) >= 0) {
        int n = b;
        path.push_front(b);
        while (n != a)
            path.push_front(n = nodes[n].pred);
    }

    return path;
}
