#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

WordMean::WordMean(string w, string m) : word(w), meaning(m) {}

string WordMean::getWord() const { return word; }

string WordMean::getMeaning() const { return meaning; }

void WordMean::setMeaning(string m) { meaning = m; }

void WordMean::setWord(string w) { word = w; }

bool WordMean::operator<(const WordMean &other) const {
    return word < other.word;
}

BST<WordMean> Dictionary::getWords() const { return words; }

// ---------------------------------------------

// a)
void Dictionary::readFile(ifstream &f) {
    string word{}, meaning{};

    while (getline(f, word)) {
        getline(f, meaning);
        WordMean wordMean{word, meaning};
        words.insert(wordMean);
    }
}

// c)
string Dictionary::consult(string word1, WordMean &previous,
                           WordMean &next) const {
    for (auto i{words.begin()}, end{words.end()}; i != end; previous = *(i++))
        if (word1 <= (*i).getWord()) {
            next = *(i);
            break;
        }

    if (word1 == next.getWord())
        return next.getMeaning();

    return "word not found";
}

// d)
bool Dictionary::update(string word1, string mean1) {
    WordMean &found = words.find({word1, ""});

    if (found.getWord() == "") {
        words.insert({word1, mean1});
        return false;
    }

    found.setMeaning(mean1);
    return true;
}

// b)
void Dictionary::print() const {
    for (const WordMean &wordMean : words) {
        cout << wordMean.getWord() << endl << wordMean.getMeaning() << endl;
    }
}
