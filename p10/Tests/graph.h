// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "disjointSets.h"
#include "minHeap.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
    struct Edge {
        int src;    // Source node
        int dest;   // Destination node
        int weight; // An integer weight

        // For Kruskal's
        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }

        bool operator==(const Edge &other) const {
            return ((src == other.src && dest == other.dest) ||
                    (src == other.dest && dest == other.src)) &&
                   weight == other.weight;
        }
    };

    struct Node {
        int distance = INT32_MAX; // For Prim's

        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    // ----- Functions to implement in this class -----
    int prim(int v);
    int kruskal();
};

#endif
