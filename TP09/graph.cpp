// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "graph.h"

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

// Depth-First Search: example implementation
int Graph::dfs(int v) {
    if (v < 1 || v > n)
        return 0;

    cout << v << " "; // show node order
    nodes[v].visited = true;
    int count{1};
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            count += dfs(w);
    }

    return count;
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v = 1; v <= n; v++)
        nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

// ----------------------------------------------------------
// Exercício 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
int Graph::outDegree(int v) {
    if (v < 1 || v > n)
        return -1;
    return nodes[v].adj.size();
}

// ----------------------------------------------------------
// Exercício 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
int Graph::connectedComponents() {
    int i{0};

    for (Node &v : nodes)
        v.visited = false;

    for (int v{1}; v <= n; ++v)
        if (!nodes[v].visited) {
            ++i;
            dfs(v);
        }

    return i;
}

// ..............................
// b) Componente gigante
int Graph::giantComponent() {
    int i{0};

    for (Node &v : nodes)
        v.visited = false;

    for (int v{1}; v <= n; ++v)
        if (!nodes[v].visited)
            i = max(dfs(v), i);

    return i;
}

// ----------------------------------------------------------
// Exercício 3: Ordenação topológica
// ----------------------------------------------------------
list<int> Graph::topologicalSorting() {
    function<list<int>(int)> helper = [&](int v) -> list<int> {
        if (v < 1 || v > n)
            return {};

        Node &n{nodes[v]};
        if (n.visited)
            return {};

        list<int> order{};
        n.visited = true;

        for (const Edge &e : n.adj) {
            auto l{helper(e.dest)};
            order.insert(order.begin(), l.begin(), l.end());
        }

        order.insert(order.begin(), v);
        return order;
    };

    list<int> order;

    for (Node &v : nodes)
        v.visited = false;

    for (int v{1}; v <= n; ++v)
        if (!nodes[v].visited) {
            auto l{helper(v)};
            order.insert(order.begin(), l.begin(), l.end());
        }

    return order;
}

// ----------------------------------------------------------
// Exercício 4: Distâncias em grafos não pesados
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
int Graph::distance(int a, int b) {
    for (Node &v : nodes)
        v.visited = false;

    queue<pair<int, int>> q{}; // queue of unvisited nodes + their distance

    q.push({a, 0});
    nodes[a].visited = true;

    while (!q.empty()) { // while there are still unvisited nodes
        int u{q.front().first}, d{q.front().second};
        q.pop();

        if (u == b)
            return d;

        for (const Edge &e : nodes[u].adj) {
            int w{e.dest};

            if (!nodes[w].visited) {
                q.push({w, d + 1});
                nodes[w].visited = true;
            }
        }
    }

    return -1;
}

// ..............................
// b) Diâmetro
int Graph::diameter() {
    if (connectedComponents() > 1)
        return -1;

    function<int(int)> helper = [&](int v) {
        for (Node &v : nodes)
            v.visited = false;

        queue<pair<int, int>> q{}; // queue of unvisited nodes + their distance

        q.push({v, 0});
        nodes[v].visited = true;

        int maxd{0};

        while (!q.empty()) { // while there are still unvisited nodes
            int u{q.front().first}, d{q.front().second};
            q.pop();

            maxd = max(d, maxd);

            for (const Edge &e : nodes[u].adj) {
                int w{e.dest};

                if (!nodes[w].visited) {
                    q.push({w, d + 1});
                    nodes[w].visited = true;
                }
            }
        }

        return maxd;
    };

    int d{0};

    for (int v{1}; v <= n; ++v)
        d = max(d, helper(v));

    return d;
}

// ----------------------------------------------------------
// Exercício 5: To or not to be… a DAG!
// ----------------------------------------------------------
bool Graph::hasCycle() {
    vector<bool> beingVisited(n + 1, false);

    for (Node &v : nodes)
        v.visited = false;

    function<bool(int)> dfs = [&](int v) {
        nodes[v].visited = true;
        beingVisited[v] = true;

        for (auto e : nodes[v].adj) {
            int w = e.dest;
            if ((!nodes[w].visited && dfs(w)) || beingVisited[w])
                return true;
        }

        beingVisited[v] = false;

        return false;
    };

    for (int v{1}; v <= n; ++v)
        if (dfs(v))
            return true;

    return false;
}
