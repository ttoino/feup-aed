// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#include "funWithHashTables.h"
#include "hashTable.h"

#include <cctype>
#include <iostream>
#include <vector>

// Exemplo de função de hash para ints
unsigned FunWithHashTables::hashInt(const int &i) { return i; }

// Exemplo de função de hash para strings
unsigned FunWithHashTables::hashString(const string &s) {
    hash<string> h;
    return h(s);
}

// ----------------------------------------------------------
// Exercicio 1: Tabelas de Dispersão
// ----------------------------------------------------------

// ..............................
// d) Contando diferentes somas de pares
int FunWithHashTables::sumPairs(const vector<int> &numbers) {
    HashTable<int> table(numbers.size() * numbers.size() + 1, hashInt);

    for (const int &n1 : numbers)
        for (const int &n2 : numbers)
            if (n1 != n2)
                table.insert(n1 + n2);

    return table.getNumActive();
}

// ----------------------------------------------------------
// Exercicio 2: Um padrão no DNA
// ----------------------------------------------------------s
int FunWithHashTables::dnaMotifs(string dna, int k,
                                 unordered_set<string> &motifs) {
    unordered_map<string, unsigned> freq{};
    size_t n{dna.size()};

    for (unsigned i{0}; i < n - k + 1; ++i)
        ++freq[dna.substr(i, k)];

    unsigned maxFreq{0};
    for (auto p : freq) {
        if (maxFreq < p.second) {
            motifs.clear();
            maxFreq = p.second;
        }

        if (p.second == maxFreq)
            motifs.insert(p.first);
    }

    return maxFreq;
}

// ----------------------------------------------------------
// Exercicio 3: Torre de Babel
// ----------------------------------------------------------
vector<string> split(const string &text) {
    vector<string> v{};
    string s{};
    for (const char &c : text) {
        if (isalpha(c))
            s += tolower(c);
        else {
            v.push_back(s);
            s = "";
        }
    }
    v.push_back(s);
    return v;
}

void FunWithHashTables::findLanguage(
    string text, const unordered_map<string, vector<string>> &dict,
    unordered_map<string, int> &answer) {
    auto words{split(text)};

    unordered_map<string, vector<string>> newDict{};
    for (const auto &p : dict) {
        answer[p.first] = 0;
        for (const auto &s : p.second)
            newDict[s].push_back(p.first);
    }

    for (const auto &word : words)
        for (const auto &lang : newDict[word])
            ++answer[lang];
}

// ----------------------------------------------------------
// Exercicio 4: Palavras Alienígenas
// ----------------------------------------------------------
unordered_map<string, unsigned> FunWithHashTables::wordMap{};

void FunWithHashTables::wordIndex(const vector<string> &words,
                                  vector<int> &answer) {
    if (wordMap.empty()) {
        unsigned i{0};
        for (int fifth{-4}; fifth < 26; ++fifth) {
            for (int fourth{fifth + 1}; fourth < 26; ++fourth) {
                for (int third{fourth + 1}; third < 26; ++third) {
                    for (int second{third + 1}; second < 26; ++second) {
                        for (int first{second + 1}; first < 26; ++first) {
                            string s{};

                            if (fifth >= 0)
                                s += 'a' + fifth;
                            if (fourth >= 0)
                                s += 'a' + fourth;
                            if (third >= 0)
                                s += 'a' + third;
                            if (second >= 0)
                                s += 'a' + second;

                            s += 'a' + first;

                            wordMap.insert({s, ++i});
                        }
                    }
                    if (third < -1)
                        third = -1;
                }
                if (fourth < -1)
                    fourth = -1;
            }
            if (fifth < -1)
                fifth = -1;
        }
    }

    for (const auto &word : words)
        answer.push_back(wordMap[word]);
}
