#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

unsigned int Game::numberOfWords(string phrase) {
    if (phrase.length() == 0)
        return 0;

    unsigned n = 1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos + 1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

Game::Game() { this->kids.clear(); }

Game::Game(list<Kid> &l2) { this->kids = l2; }

//-----------------------------------------------------------------

// a)
void Game::addKid(const Kid k1) { kids.push_back(k1); }

list<Kid> Game::getKids() const { return kids; }

void Game::setKids(const list<Kid> &l1) { kids = l1; }

// b)
Kid Game::loseGame(string phrase) {
    unsigned int n{numberOfWords(phrase)};

    auto k{kids.begin()}, end{kids.end()};
    while (kids.size() > 1) {
        for (size_t i{0}, f{(n - 1) % kids.size()}; i < f; ++i)
            if (++k == end)
                k = kids.begin();

        k = kids.erase(k);

        if (k == end)
            k = kids.begin();
    }

    return kids.front();
}

// d)
list<Kid> Game::removeOlder(unsigned id) {
    list<Kid> removed{};

    for (auto i{kids.begin()}, end = kids.end(); i != end; ++i)
        if ((*i).getAge() > id) {
            removed.push_back(*i);
            kids.erase(i--);
        }

    return removed;
}

// c)
queue<Kid> Game::rearrange() {
    queue<Kid> male{}, female{};

    for (const Kid &k : kids)
        if (k.getSex() == 'm')
            male.push(k);
        else
            female.push(k);

    size_t n{female.size()}, m{male.size()}, nm{}, nf{};

    if (n < m) {
        nf = 1;
        nm = m / n;
    } else {
        nf = n / m;
        nm = 1;
    }

    setKids({});
    while (male.size() && female.size()) {
        for (int i{0}; i < nf; ++i) {
            addKid(female.front());
            female.pop();
        }
        for (int i{0}; i < nm; ++i) {
            addKid(male.front());
            male.pop();
        }
    }

    return male.size() ? male : female;
}

// e)
bool Game::operator==(Game &g2) {
    if (kids.size() != g2.kids.size())
        return false;

    for (auto i{kids.begin()}, j{g2.kids.begin()}, end{kids.end()}; i != end;
         ++i, ++j)
        if (!(*i == *j))
            return false;

    return true;
}

// f)
list<Kid> Game::shuffle() const {
    list<Kid> kids{this->kids};
    list<Kid> l{};

    while (kids.size()) {
        int n = rand() % kids.size();
        auto k{kids.begin()};
        for (int i{0}; i < n; ++i, ++k)
            ;
        l.push_back(*k);
        kids.erase(k);
    }

    return l;
}
