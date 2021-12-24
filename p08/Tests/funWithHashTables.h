// AED 2021/2022 - Aula Pratica 08
// Pedro Ribeiro (DCC/FCUP) [12/12/2021]

#ifndef _FUNHASHTABLES_H_
#define _FUNHASHTABLES_H_

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class FunWithHashTables {
private:
    static unordered_map<string, unsigned> wordMap;

public:
    static unsigned hashInt(const int &i);
    static unsigned hashString(const string &i);

    static int sumPairs(const vector<int> &numbers);
    static int dnaMotifs(string dna, int k, unordered_set<string> &motifs);
    static void findLanguage(string text,
                             const unordered_map<string, vector<string>> &dict,
                             unordered_map<string, int> &answer);
    static void wordIndex(const vector<string> &words, vector<int> &answer);
};

#endif
