// AED 2021/2022 - Aula Pratica 07
// Pedro Ribeiro (DCC/FCUP) [06/12/2012]

#include "funWithBSTs.h"
#include "bst.h"
#include <algorithm>
#include <map>
#include <set>

// ----------------------------------------------------------
// Exercicio 1: Colecao de Cromos
// ----------------------------------------------------------
int FunWithBSTs::newBag(const vector<int> &collection, const vector<int> &bag) {
    // O(n log n)
    std::set<int> new_bag{collection.begin(), collection.end()};

    // O(1)
    size_t old_length{new_bag.size()};

    // O(n log n)
    new_bag.insert(bag.begin(), bag.end());

    // O(1)
    return new_bag.size() - old_length;
}

// ----------------------------------------------------------
// Exercicio 2: Batalha de Pokemons
// ----------------------------------------------------------
int FunWithBSTs::battle(const vector<int> &alice, const vector<int> &bruno) {
    // O(n log n)
    std::multiset<int> al{alice.begin(), alice.end()},
        br{bruno.begin(), bruno.end()};
    int a, b;

    // O(n log n)
    while (al.size() && br.size()) {
        // O(1) (I think)
        a = al.extract(--al.cend()).value();
        b = br.extract(--br.cend()).value();

        // O(log n)
        if (a < b)
            br.insert(b - a);
        else if (b < a)
            al.insert(a - b);
    }

    return al.size() - br.size();
}

// ----------------------------------------------------------
// Exercicio 3: Reviews Cinematograficas
// ----------------------------------------------------------

// ..............................
// a) Contando Filmes
int FunWithBSTs::numberMovies(const vector<pair<string, int>> &reviews) {
    // O(n log n)
    return map<string, int>(reviews.begin(), reviews.end()).size();
}

// ..............................
// b) O filme com mais reviews
void FunWithBSTs::moreReviews(const vector<pair<string, int>> &reviews, int &m,
                              int &n) {
    std::map<string, int> counter{};
    std::map<int, int> metacounter{};

    int i{0};
    m = 0, n = 0;
    for (const auto &p : reviews) {
        i = ++counter[p.first];
        ++metacounter[i];
        m = std::max(m, i);
    }
    n = metacounter[m];
}

// ..............................
// c) Os melhores filmes
vector<string> FunWithBSTs::topMovies(const vector<pair<string, int>> &reviews,
                                      double k) {
    std::map<string, int> counter{};
    std::map<string, float> means{};

    // O(n log n)
    for (const auto &p : reviews)
        means[p.first] =
            (means[p.first] * counter[p.first] + p.second) / ++counter[p.first];

    vector<string> answer{};

    // O(n)
    for (const auto &p : means)
        if (p.second >= k)
            answer.push_back(p.first);

    return answer;
}
